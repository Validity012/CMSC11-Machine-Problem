#include "paths.h"

#include "raylib.h"

#include <stdio.h>

/* Purpose: Find an asset next to the executable (installed) or in the source
 * tree (development build).
 * Parameters: name (by address) is the path under Assets/, such as
 * "sprites/character/lee_3.png".
 * Returns: a pointer to a static buffer holding the resolved path. */
const char *asset_path(const char *name)
{
    static char path[4096];
    int length = snprintf(path, sizeof path, "%sAssets/%s",
                          GetApplicationDirectory(), name);

    if (length >= 0 && length < (int)sizeof path && FileExists(path)) {
        return path;
    }

    snprintf(path, sizeof path, "%s%s", ASSETS_PATH, name);
    return path;
}
