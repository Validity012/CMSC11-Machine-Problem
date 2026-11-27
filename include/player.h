#ifndef PLAYER_H
#define PLAYER_H

#include <stdbool.h>

/* Tile constants. Move these to level.h once level.c owns the tile map. */
#define TILE_SIZE 32
#define TILE_EMPTY 0
#define TILE_SOLID 1
#define TILE_LADDER 2
#define PLAYER_WIDTH 44
#define PLAYER_HEIGHT (TILE_SIZE * 2) /* 64px: 2x taller than the 1-tile first shelf */
#define PLAYER_MAX_HEARTS 3
#define PLAYER_START_LIVES 3
#define BUBBLES_PER_1UP 75 /* proposal says 75, README says 70: confirm with the team */

/* One frame of player input, filled by player_read_input(). */
typedef struct {
    bool left;
    bool right;
    bool run;              /* Left Shift held: Lee runs instead of walks */
    bool up;
    bool down;
    bool jump_pressed;
    bool jump_held;
    bool stomp_pressed;
    bool climb_pressed;
    bool shoot_pressed;
} player_input_t;

/* All state that belongs to Lee. */
typedef struct {
    float x;
    float y;
    float vx;
    float vy;
    int facing;            /* 1 = right, -1 = left */
    bool on_ground;
    bool climbing;
    bool running;          /* true while Lee is in run mode (Left Shift on the ground) */
    bool gliding;
    bool stomping;
    bool has_towel;        /* unlocks glide */
    bool has_toothpaste;   /* unlocks shooting */
    bool has_soap;         /* key to the bath */
    bool shot_fired;       /* true for one frame when a projectile should spawn */
    int hearts;
    int lives;
    int bubbles;
    float shoot_cooldown;
    float invulnerable_timer;
} player_t;

void player_init(player_t *p, float x, float y);
void player_read_input(player_input_t *in);
void player_update(player_t *p, const player_input_t *in, const int *tiles,
                   int cols, int rows, float dt);
void player_stomp_bounce(player_t *p);
bool player_take_hit(player_t *p);
bool player_lose_life(player_t *p);
void player_respawn(player_t *p, float x, float y);
void player_add_bubbles(player_t *p, int count);

#endif
