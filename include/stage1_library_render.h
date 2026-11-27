#ifndef STAGE1_LIBRARY_RENDER_H
#define STAGE1_LIBRARY_RENDER_H

#include "player.h"

void stage1_library_render_init(void);
void stage1_library_render_world(void);
void stage1_library_render_player(const player_t *p);
void stage1_library_render_cleanup(void);

#endif
