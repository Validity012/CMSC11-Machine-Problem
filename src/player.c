#include <math.h>
#include "raylib.h"
#include "player.h"

#define WALK_SPEED 150.0f       /* default: Lee walks */
#define RUN_SPEED 270.0f        /* holding Left Shift */
#define WALK_ACCEL 1200.0f
#define RUN_ACCEL 650.0f        /* slower to build up: running has momentum */
#define WALK_FRICTION 1400.0f
#define RUN_FRICTION 700.0f     /* running Lee takes longer to stop */
#define TURN_DECEL 1800.0f      /* braking when reversing direction */
#define AIR_CONTROL 0.6f        /* fraction of ground acceleration in the air */
#define AIR_DRAG 150.0f
#define RUN_JUMP_BONUS 0.12f    /* extra jump speed per px/s of horizontal speed */
#define JUMP_SPEED 600.0f
#define JUMP_CUT_SPEED 200.0f
#define GRAVITY 1500.0f
#define MAX_FALL_SPEED 700.0f
#define GLIDE_FALL_SPEED 80.0f
#define STOMP_SPEED 900.0f
#define STOMP_BOUNCE_SPEED 500.0f
#define CLIMB_SPEED 120.0f
#define SHOOT_COOLDOWN 0.4f
#define INVULNERABLE_TIME 1.5f
#define EDGE_EPSILON 0.01f

/*
 * Purpose: Look up a tile, treating the left/right map edges as walls and
 *          anything above or below the map as empty (so Lee can fall in pits).
 * Parameters: tiles (by address, read only), cols, rows, tx, ty (by value)
 * Returns: the tile code at (tx, ty)
 */
static int tile_at(const int *tiles, int cols, int rows, int tx, int ty)
{
    if (tx < 0 || tx >= cols) {
        return TILE_SOLID;
    }
    if (ty < 0 || ty >= rows) {
        return TILE_EMPTY;
    }
    return tiles[ty * cols + tx];
}

/*
 * Purpose: Check whether Lee's box at (x, y) overlaps any solid tile.
 * Parameters: x, y (by value), tiles (by address, read only), cols, rows (by value)
 * Returns: true if the box touches a solid tile, false otherwise
 */
static bool rect_hits_solid(float x, float y, const int *tiles, int cols, int rows)
{
    int left = (int)floorf(x / TILE_SIZE);
    int right = (int)floorf((x + PLAYER_WIDTH - EDGE_EPSILON) / TILE_SIZE);
    int top = (int)floorf(y / TILE_SIZE);
    int bottom = (int)floorf((y + PLAYER_HEIGHT - EDGE_EPSILON) / TILE_SIZE);
    int tx;
    int ty;

    for (ty = top; ty <= bottom; ty++) {
        for (tx = left; tx <= right; tx++) {
            if (tile_at(tiles, cols, rows, tx, ty) == TILE_SOLID) {
                return true;
            }
        }
    }
    return false;
}

/*
 * Purpose: Check whether the center of Lee's body is inside a ladder tile.
 * Parameters: p (by address, read only), tiles (by address, read only), cols, rows (by value)
 * Returns: true if Lee overlaps a ladder, false otherwise
 */
static bool player_on_ladder(const player_t *p, const int *tiles, int cols, int rows)
{
    int tx = (int)floorf((p->x + PLAYER_WIDTH / 2.0f) / TILE_SIZE);
    int ty = (int)floorf((p->y + PLAYER_HEIGHT / 2.0f) / TILE_SIZE);

    return tile_at(tiles, cols, rows, tx, ty) == TILE_LADDER;
}

/*
 * Purpose: Move Lee horizontally and snap him out of any wall he hits.
 * Parameters: p (by address, modified), tiles (by address, read only),
 *             cols, rows, dt (by value)
 * Returns: nothing
 */
static void move_x(player_t *p, const int *tiles, int cols, int rows, float dt)
{
    p->x += p->vx * dt;
    if (rect_hits_solid(p->x, p->y, tiles, cols, rows)) {
        if (p->vx > 0.0f) {
            p->x = floorf((p->x + PLAYER_WIDTH - EDGE_EPSILON) / TILE_SIZE) * TILE_SIZE
                   - PLAYER_WIDTH;
        } else {
            p->x = (floorf(p->x / TILE_SIZE) + 1.0f) * TILE_SIZE;
        }
        p->vx = 0.0f;
    }
}

/*
 * Purpose: Move Lee vertically, then handle landing and bonking his head.
 * Parameters: p (by address, modified), tiles (by address, read only),
 *             cols, rows, dt (by value)
 * Returns: nothing
 */
static void move_y(player_t *p, const int *tiles, int cols, int rows, float dt)
{
    p->on_ground = false;
    p->y += p->vy * dt;
    if (rect_hits_solid(p->x, p->y, tiles, cols, rows)) {
        if (p->vy > 0.0f) {
            p->y = floorf((p->y + PLAYER_HEIGHT - EDGE_EPSILON) / TILE_SIZE) * TILE_SIZE
                   - PLAYER_HEIGHT;
            p->on_ground = true;
            p->stomping = false;
            p->climbing = false;
        } else {
            p->y = (floorf(p->y / TILE_SIZE) + 1.0f) * TILE_SIZE;
        }
        p->vy = 0.0f;
    }
}

/*
 * Purpose: Move a value toward a target by at most step, without overshooting.
 * Parameters: value, target, step (by value; step must not be negative)
 * Returns: the new value
 */
static float approach(float value, float target, float step)
{
    if (value < target) {
        value += step;
        if (value > target) {
            value = target;
        }
    } else if (value > target) {
        value -= step;
        if (value < target) {
            value = target;
        }
    }
    return value;
}

/*
 * Purpose: Update Lee's horizontal speed. Walking is the default; holding
 *          Left Shift on the ground switches to running, which has a higher
 *          top speed but slower acceleration, braking, and air control.
 *          Run mode is locked in at takeoff, so Lee keeps his momentum
 *          through a jump.
 * Parameters: p (by address, modified), in (by address, read only),
 *             dir (-1, 0, or 1), dt (by value)
 * Returns: nothing
 */
static void apply_horizontal(player_t *p, const player_input_t *in, int dir, float dt)
{
    float max_speed;
    float accel;
    float friction;

    if (p->on_ground) {
        p->running = in->run;
    }
    if (p->stomping) {
        p->vx = 0.0f;
        return;
    }

    max_speed = p->running ? RUN_SPEED : WALK_SPEED;
    if (dir != 0) {
        accel = p->running ? RUN_ACCEL : WALK_ACCEL;
        if (p->vx * dir < 0.0f) {
            accel = TURN_DECEL;
        }
        if (!p->on_ground) {
            accel *= AIR_CONTROL;
        }
        p->vx = approach(p->vx, dir * max_speed, accel * dt);
    } else {
        if (p->on_ground) {
            friction = p->running ? RUN_FRICTION : WALK_FRICTION;
        } else {
            friction = AIR_DRAG;
        }
        p->vx = approach(p->vx, 0.0f, friction * dt);
    }
}

/*
 * Purpose: Set Lee to his starting state at (x, y).
 * Parameters: p (by address, modified), x, y (by value)
 * Returns: nothing
 */
void player_init(player_t *p, float x, float y)
{
    p->x = x;
    p->y = y;
    p->vx = 0.0f;
    p->vy = 0.0f;
    p->facing = 1;
    p->on_ground = false;
    p->climbing = false;
    p->running = false;
    p->gliding = false;
    p->stomping = false;
    p->has_towel = false;
    p->has_toothpaste = false;
    p->has_soap = false;
    p->shot_fired = false;
    p->hearts = PLAYER_MAX_HEARTS;
    p->lives = PLAYER_START_LIVES;
    p->bubbles = 0;
    p->shoot_cooldown = 0.0f;
    p->invulnerable_timer = 0.0f;
}

/*
 * Purpose: Read the keyboard and mouse into one frame of input.
 *          Left/Right or A/D move (Left Shift runs), Up/Down or W/S climb, Space jumps/glides,
 *          Q stomps, E grabs or lets go of a ladder, left click shoots.
 * Parameters: in (by address, modified)
 * Returns: nothing
 */
void player_read_input(player_input_t *in)
{
    in->left = IsKeyDown(KEY_LEFT) || IsKeyDown(KEY_A);
    in->right = IsKeyDown(KEY_RIGHT) || IsKeyDown(KEY_D);
    in->run = IsKeyDown(KEY_LEFT_SHIFT);
    in->up = IsKeyDown(KEY_UP) || IsKeyDown(KEY_W);
    in->down = IsKeyDown(KEY_DOWN) || IsKeyDown(KEY_S);
    in->jump_pressed = IsKeyPressed(KEY_SPACE);
    in->jump_held = IsKeyDown(KEY_SPACE);
    in->stomp_pressed = IsKeyPressed(KEY_Q);
    in->climb_pressed = IsKeyPressed(KEY_E);
    in->shoot_pressed = IsMouseButtonPressed(MOUSE_BUTTON_LEFT);
}

/*
 * Purpose: Advance Lee by one frame: climbing, jumping, gliding, stomping,
 *          shooting, gravity, and tile collision.
 * Parameters: p (by address, modified), in (by address, read only),
 *             tiles (by address, read only), cols, rows, dt (by value)
 * Returns: nothing
 */
void player_update(player_t *p, const player_input_t *in, const int *tiles,
                   int cols, int rows, float dt)
{
    int dir = (in->right ? 1 : 0) - (in->left ? 1 : 0);
    int climb_dir = (in->down ? 1 : 0) - (in->up ? 1 : 0);
    bool on_ladder = player_on_ladder(p, tiles, cols, rows);
    float max_fall;

    p->shot_fired = false;
    if (p->shoot_cooldown > 0.0f) {
        p->shoot_cooldown -= dt;
    }
    if (p->invulnerable_timer > 0.0f) {
        p->invulnerable_timer -= dt;
    }
    if (dir != 0) {
        p->facing = dir;
    }

    /* E grabs a ladder when overlapping one, and lets go when already on it. */
    if (in->climb_pressed) {
        if (p->climbing) {
            p->climbing = false;
        } else if (on_ladder) {
            p->climbing = true;
            p->stomping = false;
            p->vx = 0.0f;
            p->vy = 0.0f;
        }
    }
    if (p->climbing && !on_ladder) {
        p->climbing = false;
    }

    if (p->climbing) {
        p->vx = 0.0f;
        p->running = false;
        p->vy = climb_dir * CLIMB_SPEED;
        p->gliding = false;
        if (in->jump_pressed) {
            p->climbing = false;
            p->vy = -JUMP_SPEED;
            p->vx = dir * WALK_SPEED;
        }
    } else {
        apply_horizontal(p, in, dir, dt);

        if (in->jump_pressed && p->on_ground) {
            /* Faster horizontal speed gives a slightly higher jump. */
            p->vy = -(JUMP_SPEED + fabsf(p->vx) * RUN_JUMP_BONUS);
            p->on_ground = false;
        }
        /* Releasing Space early cuts the jump short (hold for a higher jump). */
        if (!in->jump_held && !p->stomping && p->vy < -JUMP_CUT_SPEED) {
            p->vy = -JUMP_CUT_SPEED;
        }
        /* Q while airborne dives straight down. */
        if (in->stomp_pressed && !p->on_ground && !p->stomping) {
            p->stomping = true;
        }
        /* Holding Space while falling glides, but only after the towel. */
        p->gliding = p->has_towel && in->jump_held && !p->on_ground
                     && !p->stomping && p->vy > 0.0f;

        if (p->stomping) {
            p->vy = STOMP_SPEED;
        } else {
            max_fall = p->gliding ? GLIDE_FALL_SPEED : MAX_FALL_SPEED;
            p->vy += GRAVITY * dt;
            if (p->vy > max_fall) {
                p->vy = max_fall;
            }
        }
    }

    /* Left click shoots, but only after the toothpaste and off cooldown. */
    if (in->shoot_pressed && p->has_toothpaste && p->shoot_cooldown <= 0.0f) {
        p->shot_fired = true;
        p->shoot_cooldown = SHOOT_COOLDOWN;
    }

    move_x(p, tiles, cols, rows, dt);
    move_y(p, tiles, cols, rows, dt);
}

/*
 * Purpose: Bounce Lee upward after he lands on an enemy (called by enemy.c).
 * Parameters: p (by address, modified)
 * Returns: nothing
 */
void player_stomp_bounce(player_t *p)
{
    p->vy = -STOMP_BOUNCE_SPEED;
    p->stomping = false;
    p->on_ground = false;
}

/*
 * Purpose: Remove one heart unless Lee is still invulnerable from a recent hit.
 * Parameters: p (by address, modified)
 * Returns: true if the hearts just ran out, false otherwise
 */
bool player_take_hit(player_t *p)
{
    if (p->invulnerable_timer > 0.0f) {
        return false;
    }
    p->hearts--;
    p->invulnerable_timer = INVULNERABLE_TIME;
    return p->hearts <= 0;
}

/*
 * Purpose: Take away one life (hearts ran out or Lee fell into a pit).
 * Parameters: p (by address, modified)
 * Returns: true if no lives are left (Game Over), false otherwise
 */
bool player_lose_life(player_t *p)
{
    p->lives--;
    return p->lives <= 0;
}

/*
 * Purpose: Put Lee back at the level start with full hearts. Items, lives,
 *          and the bubble count are kept.
 * Parameters: p (by address, modified), x, y (by value)
 * Returns: nothing
 */
void player_respawn(player_t *p, float x, float y)
{
    p->x = x;
    p->y = y;
    p->vx = 0.0f;
    p->vy = 0.0f;
    p->on_ground = false;
    p->climbing = false;
    p->running = false;
    p->gliding = false;
    p->stomping = false;
    p->hearts = PLAYER_MAX_HEARTS;
    p->invulnerable_timer = 0.0f;
}

/*
 * Purpose: Add popped bubbles and grant a 1UP at every BUBBLES_PER_1UP.
 * Parameters: p (by address, modified), count (by value)
 * Returns: nothing
 */
void player_add_bubbles(player_t *p, int count)
{
    int i;

    for (i = 0; i < count; i++) {
        p->bubbles++;
        if (p->bubbles % BUBBLES_PER_1UP == 0) {
            p->lives++;
        }
    }
}
