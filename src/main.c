#include "game.h"
#include "raylib.h"

/* Purpose: Run the game window and frame loop.
- Parameters: None.
- Returns: 0 on normal exit.
- TG 26: Creating the initial Scaffold
- TG 27: Implementing the main loop
- TG 28: Implementing collision detection and a LOT of testing t-t
 */
int main(void)
{
    const char *title = "Lee Go!";
    InitWindow(1280, 720, title);
    SetTargetFPS(60);
    SetExitKey(KEY_NULL); // Lets ESC return to menu instead of instantly closing the window

    game_init();

    while (!WindowShouldClose() && !game_should_exit()) {
        game_update();
        game_draw();
    }

    game_cleanup();
    CloseWindow();
    return 0;
}
