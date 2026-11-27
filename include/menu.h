#ifndef MENU_H
#define MENU_H

typedef enum {
    MENU_NONE = 0,
    MENU_PLAY = 1,
    MENU_EXIT = 2
} MenuAction;

void init_menu(void);
MenuAction update_menu(void);
void draw_menu(void);

#endif
