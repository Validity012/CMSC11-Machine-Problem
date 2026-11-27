#ifndef STAGE1_LIBRARY_H
#define STAGE1_LIBRARY_H

#include "raylib.h"
#include "player.h"

#define CHUNK1_ROWS 16
#define CHUNK1_COLS 55

void stage1_library_init(int *tiles_out, Vector2 *spawn_out);
void stage1_library_update(const player_t *p, float dt);

char stage1_library_get_char(int col, int row);
Camera2D stage1_library_get_camera(void);
int stage1_library_get_lee_frame(void);
int stage1_library_get_wind_frame(void);
Vector2 stage1_library_get_fan_pos(void);

#endif
