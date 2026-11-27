#include "raylib.h"
#include "menu.h"

typedef struct menuItems {
    MenuAction action;
    char label[20];
    Rectangle bounds;
} MenuItem;

static MenuItem options[2];

void init_menu(void) {
    // 1280x720 screen -> (1280 - 200) / 2 = 540.0f
    options[0] = (MenuItem){ MENU_PLAY, "Play", { 540.0f, 280.0f, 200.0f, 50.0f } };
    options[1] = (MenuItem){ MENU_EXIT, "Exit", { 540.0f, 360.0f, 200.0f, 50.0f } };
}

MenuAction update_menu(void) {
    Vector2 mousePos = GetMousePosition();

    for (int i = 0; i < 2; i++) {
        if (CheckCollisionPointRec(mousePos, options[i].bounds) &&
            IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
            return options[i].action;
        }
    }

    return MENU_NONE;
}

void draw_menu(void) {
    Vector2 mousePos = GetMousePosition();

    DrawText("Lee Go!", (1280 - MeasureText("Lee Go!", 48)) / 2, 160, 48, BLACK);

    for (int i = 0; i < 2; i++) {
        Color boxColor = DARKGRAY;

        if (CheckCollisionPointRec(mousePos, options[i].bounds)) {
            boxColor = GRAY;
        }

        DrawRectangleRec(options[i].bounds, boxColor);
        DrawText(
            options[i].label,
            (int)options[i].bounds.x + 20,
            (int)options[i].bounds.y + 15,
            20,
            WHITE
        );
    }
}
