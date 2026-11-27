#include "game.h"
#include "menu.h"
#include "level.h"
#include "raylib.h"

static GameState current_state;
static bool exit_requested = false;

// --- Temporary collision test variables (can be moved to level.c later) ---
static Rectangle lee = {100, 280, 24, 32};
static Rectangle blue_lee = {100, 50, 24, 32};
static Rectangle tile = {96, 300, 64, 64};

static Rectangle solids[] = {
    {64, 400, 640, 32},
    {300, 336, 32, 64},
    {400, 250, 128, 32},
    {520, 320, 128, 16}
};
static const int solid_count = (int)(sizeof(solids) / sizeof(solids[0]));

static CollisionResult floor_test;
static CollisionResult wall_test;
static CollisionResult ceiling_test;
static CollisionResult edge_test;
static Color lee_color;
// --------------------------------------------------------------------------

void game_init(void) {
    current_state = STATE_MENU;
    exit_requested = false;
    init_menu();
}

void game_update(void) {
    switch (current_state) {
        case STATE_MENU: {
            MenuAction action = update_menu();
            if (action == MENU_PLAY) {
                current_state = STATE_GAMEPLAY;
            } else if (action == MENU_EXIT) {
                exit_requested = true;
            }
            break;
        }

        case STATE_GAMEPLAY: {
            // Return to menu when ESC is pressed
            if (IsKeyPressed(KEY_ESCAPE)) {
                current_state = STATE_MENU;
                break;
            }

            // Collision tests
            const float dx = 16.0f;
            const float dy = 16.0f;

            floor_test = resolve_collisions(
                (Rectangle){100, 360, 24, 32}, 0.0f, dy, solids, solid_count);
            wall_test = resolve_collisions(
                (Rectangle){268, 336, 24, 32}, dx, 0.0f, solids, solid_count);
            ceiling_test = resolve_collisions(
                (Rectangle){420, 290, 24, 32}, 0.0f, -dy, solids, solid_count);
            edge_test = resolve_collisions(
                (Rectangle){632, 288, 24, 32}, dx, 0.0f, solids, solid_count);

            lee_color = overlaps_solid_tile(lee, tile) ? RED : BLUE;
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
            ClearBackground(GRAY);

            for (int i = 0; i < solid_count; i++) {
                DrawRectangleRec(solids[i], DARKGRAY);
            }
            DrawRectangleRec(tile, DARKGRAY);
            DrawRectangleRec(blue_lee, BLUE);
            DrawRectangleRec(lee, lee_color);

            DrawRectangleRec(floor_test.rect,
                             floor_test.blocked_y && floor_test.on_ground ? GREEN : MAROON);
            DrawRectangleRec(wall_test.rect,
                             wall_test.blocked_x ? YELLOW : ORANGE);
            DrawRectangleRec(ceiling_test.rect,
                             ceiling_test.blocked_y ? PURPLE : PINK);
            DrawRectangleRec(edge_test.rect,
                             edge_test.on_ground ? LIME : RED);
            DrawText("Lee Go!", 40, 40, 32, BLACK);
            break;
    }

    EndDrawing();
}

bool game_should_exit(void) {
    return exit_requested;
}

void game_cleanup(void) {
    // Cleanup resources here later
}
