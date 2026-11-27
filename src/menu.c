#include "raylib.h"
#include "menu.h"

typedef struct menuItems {
    int id;
    char label[20];
    Rectangle bounds; //Nested Struct: holds x,y,width, and height
} MenuItem;

/* Purpose: Show the Play/Exit menu and return the chosen id (1 or 0).
 * Mouse hover/click and Up/Down plus Enter both work. */
int runMenu (void) {
    MenuItem options[2] = {
        //assuming the screen is a standard 16:9
        {1, "Play",{540.0f, 280.0f, 200.0f, 50.0f}},
        {0, "Exit",{540.0f, 360.0f, 200.0f, 50.0f}},
        };
    const int count = 2;
    int selected = 0;

    //WindowShouldClose: returns False if window is open, True if not
    //This while loop runs 60 times per sec, as stated in the main.c
    while (!WindowShouldClose()) {
        Vector2 mousePos = GetMousePosition();

        // Up/Down moves the selection from the keyboard.
        if (IsKeyPressed(KEY_DOWN)) {
            selected = (selected + 1) % count;
        }
        if (IsKeyPressed(KEY_UP)) {
            selected = (selected + count - 1) % count;
        }

        for (int i = 0; i < count; i++) {

            // The mouse moves the selection and clicks activate it.
            if (CheckCollisionPointRec(mousePos, options[i].bounds)) {
                selected = i;
                if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {

                    // Immediately exits runMenu() and sends this button's id (1 or 0) back to main.c
                    return options[i].id;
                }
            }
        }

        if (IsKeyPressed(KEY_ENTER) || IsKeyPressed(KEY_KP_ENTER)) {
            return options[selected].id;
        }

        BeginDrawing();
        ClearBackground(RAYWHITE);

        for (int i = 0; i < count; i++) {
            // The selected option is highlighted.
            Color boxColor = (i == selected) ? MAROON : DARKGRAY;

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

        DrawText("Up/Down to choose, Enter to select",
                 500, 450, 20, DARKGRAY);
        EndDrawing();
    }
    return 0;
}
