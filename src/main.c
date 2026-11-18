#include "raylib.h"
#include "menu.h"

int main(void) {
    InitWindow(1280, 720, "Lee Go!");
    SetTargetFPS(60);

    int choice = 1;
    //WindowShouldClose checks if window is still open
    while (choice != 0 && !WindowShouldClose()) {
        choice = runMenu();

        if (choice == 1) {
            startGame();
        }
    }

    CloseWindow();
    return 0;
}
