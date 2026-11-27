#ifndef PATHS_H
#define PATHS_H

#ifndef ASSETS_PATH
#define ASSETS_PATH "Assets/"
#endif

#ifndef LEVELS_PATH
#define LEVELS_PATH "levels/"
#endif

/* Returns the path to an asset, preferring the copy next to the executable. */
const char *asset_path(const char *name);

#endif
