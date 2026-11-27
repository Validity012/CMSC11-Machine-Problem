#include "game.h"
#include "menu.h"
#include "paths.h"
#include "player.h"
#include "raylib.h"
#include "stage1_library.h"
#include "stage1_library_render.h"

static GameState current_state;
static bool exit_requested = false;

static int tiles[CHUNK1_COLS * CHUNK1_ROWS];
static Vector2 stage1_spawn;
static player_t player;
static player_input_t input;

void game_init(void) {
    current_state = STATE_MENU;
    exit_requested = false;
    stage1_library_init(tiles, &stage1_spawn);
    stage1_library_render_init();
    player_init(&player, stage1_spawn.x, stage1_spawn.y);
    init_menu();
}

void game_update(void) {
    switch (current_state) {
        case STATE_MENU: {
            MenuAction action = update_menu();
            if (action == MENU_PLAY) {
                stage1_library_init(tiles, &stage1_spawn);
                player_init(&player, stage1_spawn.x, stage1_spawn.y);
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
            player_update(&player, &input, tiles, CHUNK1_COLS, CHUNK1_ROWS, dt);
            stage1_library_update(&player, dt);
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
            ClearBackground((Color){ 235, 226, 210, 255 });

            BeginMode2D(stage1_library_get_camera());
                stage1_library_render_world();
                stage1_library_render_player(&player);
            EndMode2D();

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
    stage1_library_render_cleanup();
}
