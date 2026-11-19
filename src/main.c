#include "raylib.h"

/* Purpose: Run the game window and frame loop.
 * Parameters: None.
 * Returns: 0 on normal exit.
 * TG 26: Creating the initial Scaffold
 */

int main(void)
{
    // TODO: Open a 1280 × 720 window titled "Lee Go!" and target 60 FPS.
    const char *title = "Lee Go!";
    InitWindow(1280, 720, title);
    SetTargetFPS(60);

    while (!WindowShouldClose()) {
        // Future game updates go here.

        BeginDrawing();
        ClearBackground(GRAY);
        DrawText("Lee Go!", 40, 40, 32, BLACK);
        EndDrawing();
    }

    CloseWindow();
    return 0;
}