#include "raylib.h"
#include "menu.h"

typedef struct menuItems {
    int id;
    char label[20];
    Rectangle bounds; //Nested Struct: holds x,y,width, and height
} MenuItem;

int runMenu (void) {
    MenuItem options[2] = {
        //assuming the screen is a standard 16:9
        {1, "Play",{540.0f, 280.0f, 200.0f, 50.0f}},
        {0, "Exit",{540.0f, 360.0f, 200.0f, 50.0f}},
        };

    //WindowShouldClose: returns False if window is open, True if not
    //This while loop runs 60 times per sec, as stated in the main.c
    while (!WindowShouldClose()) {
        Vector2 mousePos = GetMousePosition();

        for (int i = 0; i < 2; i++) {

            // Checks two conditions: Is the cursor inside bounds && is
            if (CheckCollisionPointRec(mousePos, options[i].bounds) &&
                IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {

                // Immediately exits runMenu() and sends this button's id (1 or 0) back to main.c
                return options[i].id;
            }
        }

        BeginDrawing();
        ClearBackground(RAYWHITE);

        for (int i = 0; i < 2; i++) {
            Color boxColor = DARKGRAY; //color of the rectangle

            // Checks if the mouse is hovering over options
            if (CheckCollisionPointRec(mousePos, options[i].bounds)) {
                boxColor = GRAY;
            }

            // Draws the solid colored rectangle
            DrawRectangleRec(options[i].bounds, boxColor);

            // Draws the button
            DrawText(
                options[i].label,               // "Play or Exit
                (int)options[i].bounds.x + 20,  // Padding for right and left
                (int)options[i].bounds.y + 15,  // Padding for top and bottom
                20,                             // Font size
                WHITE                           // Text color
            );
        }
        EndDrawing();
    }
    return 0;
}
