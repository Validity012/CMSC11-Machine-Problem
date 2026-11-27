#include "game.h"
#include "player.h"
#include "raylib.h"

#define MAP_COLS 40
#define MAP_ROWS 22

/* Stand-in greybox map until the real Level 1 map is designed.
 * '#' is solid and '.' is empty. */
static const char *const demo_map[MAP_ROWS] = {
    "########################################",
    "#......................................#",
    "#......................................#",
    "#......................................#",
    "#......................................#",
    "#......................................#",
    "#......................................#",
    "#......................................#",
    "#......................................#",
    "#......................................#",
    "#......................................#",
    "#............................#######...#",
    "#......................................#",
    "#......................................#",
    "#.................#######..............#",
    "#......................................#",
    "#......................................#",
    "#......#######.........................#",
    "#......................................#",
    "#......................................#",
    "########################################",
    "########################################",
};

/* Purpose: Play one round with a fresh Lee until Esc or the window closes. */
void game_run(void)
{
    int tiles[MAP_COLS * MAP_ROWS];
    player_t player;
    player_input_t input;
    float dt;
    int row;
    int col;

    // Turn the map into the tile codes the player code expects.
    for (row = 0; row < MAP_ROWS; row++) {
        for (col = 0; col < MAP_COLS; col++) {
            tiles[row * MAP_COLS + col] =
                demo_map[row][col] == '#' ? TILE_SOLID : TILE_EMPTY;
        }
    }

    // Start Lee on the floor near the left wall.
    player_init(&player, 3 * TILE_SIZE, 20 * TILE_SIZE - PLAYER_HEIGHT);

    while (!WindowShouldClose() && !IsKeyPressed(KEY_ESCAPE)) {
        dt = GetFrameTime();
        if (dt > 0.05f) {
            dt = 0.05f;
        }

        player_read_input(&input);
        player_update(&player, &input, tiles, MAP_COLS, MAP_ROWS, dt);

        BeginDrawing();
        ClearBackground(SKYBLUE);

        for (row = 0; row < MAP_ROWS; row++) {
            for (col = 0; col < MAP_COLS; col++) {
                if (tiles[row * MAP_COLS + col] == TILE_SOLID) {
                    DrawRectangle(col * TILE_SIZE, row * TILE_SIZE,
                                  TILE_SIZE, TILE_SIZE, DARKGRAY);
                }
            }
        }

        DrawRectangle((int)player.x, (int)player.y,
                      PLAYER_WIDTH, PLAYER_HEIGHT, RED);

        // HUD bar across the top: state plus one line of controls.
        DrawRectangle(0, 0, 1280, 60, BLACK);
        DrawText(TextFormat("Hearts: %d   Lives: %d   Bubbles: %d",
                            player.hearts, player.lives, player.bubbles),
                 10, 8, 20, WHITE);
        DrawText("Arrows/A,D move   Shift run   Space jump   Q stomp"
                 "   E ladder   Esc menu",
                 10, 32, 20, WHITE);
        EndDrawing();
    }
}
