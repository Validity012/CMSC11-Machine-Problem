#include "level.h"

#include <math.h>

// Checks if Lee is lined up with a tile from left to right.
static bool horizontal_overlap(Rectangle lee, Rectangle tile)
{
    return lee.x < tile.x + tile.width &&
           lee.x + lee.width > tile.x;
}

// Lee is on the ground when its bottom is touching a tile.
static bool supported_by_tile(Rectangle lee, Rectangle tile)
{
    const float epsilon = 0.01f;

    return horizontal_overlap(lee, tile) &&
           fabsf((lee.y + lee.height) - tile.y) <= epsilon;
}

// Checks if two rectangles are overlapping.
bool overlaps_solid_tile(Rectangle lee, Rectangle tile)
{
    return CheckCollisionRecs(lee, tile);
}

CollisionResult resolve_collisions(Rectangle lee,
                                   float dx,
                                   float dy,
                                   const Rectangle *solids,
                                   int solid_count)
{
    CollisionResult result = {lee, false, false, false};

    // Move on the x-axis first and stop at the first solid tile.
    result.rect.x += dx;
    for (int i = 0; i < solid_count; i++) {
        if (!overlaps_solid_tile(result.rect, solids[i])) {
            continue;
        }

        result.blocked_x = true;
        if (dx > 0) {
            result.rect.x = fminf(result.rect.x,
                                  solids[i].x - result.rect.width);
        } else if (dx < 0) {
            result.rect.x = fmaxf(result.rect.x,
                                  solids[i].x + solids[i].width);
        }
    }

    // Move on the y-axis next and stop at the first solid tile.
    result.rect.y += dy;
    for (int i = 0; i < solid_count; i++) {
        if (!overlaps_solid_tile(result.rect, solids[i])) {
            continue;
        }

        result.blocked_y = true;
        if (dy > 0) {
            result.rect.y = fminf(result.rect.y,
                                  solids[i].y - result.rect.height);
        } else if (dy < 0) {
            result.rect.y = fmaxf(result.rect.y,
                                  solids[i].y + solids[i].height);
        }
    }

    // Check if Lee is still standing on any of the tiles.
    for (int i = 0; i < solid_count; i++) {
        if (supported_by_tile(result.rect, solids[i])) {
            result.on_ground = true;
            break;
        }
    }

    return result;
}