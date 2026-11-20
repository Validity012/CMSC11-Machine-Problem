#ifndef LEVEL_H
#define LEVEL_H

#include "raylib.h"

#include <stdbool.h>

typedef struct CollisionResult {
    Rectangle rect;
    bool blocked_x;
    bool blocked_y;
    bool on_ground;
} CollisionResult;

bool overlaps_solid_tile(Rectangle lee, Rectangle tile);

CollisionResult resolve_collisions(Rectangle lee,
                                   float dx,
                                   float dy,
                                   const Rectangle *solids,
                                   int solid_count);

#endif