#ifndef GAME_H
#define GAME_H

#include <stdbool.h>

typedef enum {
    STATE_MENU,
    STATE_GAMEPLAY
} GameState;

void game_init(void);
void game_update(void);
void game_draw(void);
bool game_should_exit(void);
void game_cleanup(void);

#endif
