#include "game.h"
#include "input.h"
#include "menu.h"
#include "raylib.h"

/* Purpose: Start the launcher, then alternate between the menu and rounds.
 * TG 26: initial scaffold and game loop
 * TG 27: main loop
 * TG 40: console launcher with validated input
 */
int main(void)
{
    // The console launcher runs before raylib opens a window.
    if (launcher_run() == LAUNCHER_QUIT) {
        return 0;
    }

    InitWindow(1280, 720, "Lee Go!");
    SetTargetFPS(60);
    // Esc leaves a round and returns to the menu instead of closing the window.
    SetExitKey(KEY_NULL);

    for (;;) {
        if (runMenu() == 0) {
            break;
        }
        game_run();
    }

    CloseWindow();
    return 0;
}
