#include "game.h"
#include "menu.h"
#include "player.h"
#include "raylib.h"

#define MAP_COLS 40
#define MAP_ROWS 22
#define SPAWN_X (3 * TILE_SIZE)
#define SPAWN_Y ((MAP_ROWS - 1) * TILE_SIZE - PLAYER_HEIGHT)

static GameState current_state;
static bool exit_requested = false;

/* Stand-in greybox map until Level 1 is designed: '#' solid, '.' empty. */
static const char *const map_rows[MAP_ROWS] = {
    "########################################", /*  0 */
    "#......................................#", /*  1 */
    "#......................................#", /*  2 */
    "#......................................#", /*  3 */
    "#......................................#", /*  4 */
    "#......................................#", /*  5 */
    "#......................................#", /*  6 */
    "#......................................#", /*  7 */
    "#......................................#", /*  8 */
    "#......................................#", /*  9 */
    "#......................................#", /* 10 */
    "#...........................#######....#", /* 11 */
    "#......................................#", /* 12 */
    "#......................................#", /* 13 */
    "#.................#######..............#", /* 14 */
    "#......................................#", /* 15 */
    "#......................................#", /* 16 */
    "#.......#######........................#", /* 17 */
    "#...##.................................#", /* 18 */
    "#......................................#", /* 19 */
    "#......................................#", /* 20 */
    "########################################"  /* 21 */
};

static int tiles[MAP_COLS * MAP_ROWS];
static player_t player;
static player_input_t input;
static Texture2D lee_texture;

/* Purpose: Convert the char map into the tile grid player_update walks on. */
static void load_map(void) {
    for (int r = 0; r < MAP_ROWS; r++) {
        for (int c = 0; c < MAP_COLS; c++) {
            tiles[r * MAP_COLS + c] = (map_rows[r][c] == '#') ? TILE_SOLID : TILE_EMPTY;
        }
    }
}

void game_init(void) {
    current_state = STATE_MENU;
    exit_requested = false;
    load_map();
    lee_texture = LoadTexture(ASSETS_PATH "sprites/character/lee_3.png");
    player_init(&player, SPAWN_X, SPAWN_Y);
    init_menu();
}

void game_update(void) {
    switch (current_state) {
        case STATE_MENU: {
            MenuAction action = update_menu();
            if (action == MENU_PLAY) {
                /* Every new run starts Lee back at the spawn. */
                player_init(&player, SPAWN_X, SPAWN_Y);
                current_state = STATE_GAMEPLAY;
            } else if (action == MENU_EXIT) {
                exit_requested = true;
            }
            break;
        }

        case STATE_GAMEPLAY: {
            float dt;

            if (IsKeyPressed(KEY_ESCAPE)) {
                current_state = STATE_MENU;
                break;
            }

            dt = GetFrameTime();
            if (dt > 0.05f) {
                dt = 0.05f;
            }

            player_read_input(&input);
            player_update(&player, &input, tiles, MAP_COLS, MAP_ROWS, dt);
            break;
        }
    }
}

void game_draw(void) {
    BeginDrawing();

    switch (current_state) {
        case STATE_MENU:
            ClearBackground(RAYWHITE);
            draw_menu();
            break;

        case STATE_GAMEPLAY:
            ClearBackground(SKYBLUE);

            for (int r = 0; r < MAP_ROWS; r++) {
                for (int c = 0; c < MAP_COLS; c++) {
                    if (tiles[r * MAP_COLS + c] == TILE_SOLID) {
                        DrawRectangle(c * TILE_SIZE, r * TILE_SIZE,
                                      TILE_SIZE, TILE_SIZE, DARKGRAY);
                    }
                }
            }

            if (lee_texture.id != 0) {
                Rectangle source = {0, 0, (float)lee_texture.width,
                                    (float)lee_texture.height};
                Rectangle dest = {player.x, player.y - 4,
                                  PLAYER_WIDTH, PLAYER_HEIGHT + 4};

                if (player.facing < 0) {
                    source.width = -source.width;
                }
                DrawTexturePro(lee_texture, source, dest, (Vector2){0, 0}, 0.0f,
                               WHITE);
            } else {
                /* Fallback when the sprite is missing. */
                DrawRectangle((int)player.x, (int)player.y,
                              PLAYER_WIDTH, PLAYER_HEIGHT, MAROON);
            }

            /* HUD strip over the top of the map. */
            DrawRectangle(0, 0, 1280, 56, Fade(BLACK, 0.55f));
            DrawText(TextFormat("Hearts: %d   Lives: %d   Bubbles: %d",
                                player.hearts, player.lives, player.bubbles),
                     16, 8, 20, WHITE);
            DrawText("Arrows/WASD move   Shift run   Space jump   Q stomp   E ladder   Esc menu",
                     16, 32, 16, LIGHTGRAY);
            break;
    }

    EndDrawing();
}

bool game_should_exit(void) {
    return exit_requested;
}

void game_cleanup(void) {
    if (lee_texture.id != 0) {
        UnloadTexture(lee_texture);
    }
}
