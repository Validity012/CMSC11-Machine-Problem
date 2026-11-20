#include "level.h"
#include "raylib.h"

/* Purpose: Run the game window and frame loop.
 * Parameters: None.
 * Returns: 0 on normal exit.
 * TG 26: Creating the initial Scaffold
 * TG 27: Implementing the main loop
 * TG 28: Implementing collision detection and a LOT of testing t-t
 */

int main(void)
{
    // Opens a 1280 x 720 window titled "Lee Go!" at 60 FPS.
    const char *title = "Lee Go!";
    InitWindow(1280, 720, title);
    SetTargetFPS(60);

    // Test rectangles for checking if Lee overlaps a tile.
    Rectangle lee = {100, 280, 24, 32};
    Rectangle blue_lee = {100, 50, 24, 32};
    Rectangle tile = {96, 300, 64, 64};

    // Test layout with a floor, wall, ceiling, and platform.
    Rectangle solids[] = {
        {64, 400, 640, 32},
        {300, 336, 32, 64},
        {400, 250, 128, 32},
        {520, 320, 128, 16}
    };
    const int solid_count = (int)(sizeof(solids) / sizeof(solids[0]));

    while (!WindowShouldClose()) {
        // Fixed values are used so no keyboard input is needed for testing.
        const float dx = 16.0f;
        const float dy = 16.0f;

        // Test Lee landing on the floor.
        CollisionResult floor_test = resolve_collisions(
            (Rectangle){100, 360, 24, 32}, 0.0f, dy, solids, solid_count);

        // Test Lee moving into the wall.
        CollisionResult wall_test = resolve_collisions(
            (Rectangle){268, 336, 24, 32}, dx, 0.0f, solids, solid_count);

        // Test Lee moving into the ceiling.
        CollisionResult ceiling_test = resolve_collisions(
            (Rectangle){420, 290, 24, 32}, 0.0f, -dy, solids, solid_count);

        // Test Lee moving past the edge of the platform.
        CollisionResult edge_test = resolve_collisions(
            (Rectangle){632, 288, 24, 32}, dx, 0.0f, solids, solid_count);

        // Lee turns red when it overlaps the tile, otherwise it stays blue.
        Color lee_color = overlaps_solid_tile(lee, tile) ? RED : BLUE;

        BeginDrawing();
        ClearBackground(GRAY);

        // Draw the tiles and the test rectangles.
        for (int i = 0; i < solid_count; i++) {
            DrawRectangleRec(solids[i], DARKGRAY);
        }
        DrawRectangleRec(tile, DARKGRAY);
        DrawRectangleRec(blue_lee, BLUE);
        DrawRectangleRec(lee, lee_color);

        // Different colors show the result of each collision test.
        DrawRectangleRec(floor_test.rect,
                         floor_test.blocked_y && floor_test.on_ground
                             ? GREEN
                             : MAROON);
        DrawRectangleRec(wall_test.rect,
                         wall_test.blocked_x ? YELLOW : ORANGE);
        DrawRectangleRec(ceiling_test.rect,
                         ceiling_test.blocked_y ? PURPLE : PINK);
        DrawRectangleRec(edge_test.rect,
                         edge_test.on_ground ? LIME : RED);
        DrawText("Lee Go!", 40, 40, 32, BLACK);
        EndDrawing();
    }

    CloseWindow();
    return 0;
}