#include "stage1_library.h"
#include <math.h>

// Chunk 1 + Chunk 2 (55 cols):
// Spawn (2) -> Fan (4) -> Hanging Shelf (6-9) -> Large Shelf (12-17) -> Tall Wall (20-22) -> Pit (23-25) -> Ledge 2 (26-34) -> 3 Static Pillars (37, 43, 49) -> End Ledge (52-54)
static const char *const CHUNK1_MAP[CHUNK1_ROWS] = {
    ".......................................................", /*  0 */
    ".......................................................", /*  1 */
    ".......................................................", /*  2 */
    ".......................................................", /*  3 */
    ".......................................................", /*  4 */
    ".......................................................", /*  5 */
    "....................###................................", /*  6 - Tall wall */
    "....................###................................", /*  7 */
    "....................###................................", /*  8 */
    "............BBBBBB..###...#########..P.....P.....P..###", /*  9 - Large shelf + Ledge 2 + 3 Pillars + End Ledge */
    "....F.......TTTTTT..###...#########.................###", /* 10 - Fan */
    "..S...LLLL..TTTTTT..###...#########.................###", /* 11 - Hanging shelf */
    "#######################^^^#########^^^^^^^^^^^^^^^^^###", /* 12 - Floor + Hazard pits */
    "#######################################################", /* 13 */
    "#######################################################", /* 14 */
    "#######################################################"  /* 15 */
};

static Camera2D camera = { 0 };
static int lee_frame = 0;
static float lee_timer = 0.0f;
static int wind_frame = 0;
static float wind_timer = 0.0f;
static Vector2 fan_pos = { 4.0f * TILE_SIZE, 10.0f * TILE_SIZE };

void stage1_library_init(int *tiles_out, Vector2 *spawn_out) {
    *spawn_out = (Vector2){ 2.0f * TILE_SIZE, 11.0f * TILE_SIZE };

    // Clear array first so multi-tile pillars don't get overwritten
    for (int i = 0; i < CHUNK1_ROWS * CHUNK1_COLS; i++) {
        tiles_out[i] = TILE_EMPTY;
    }

    for (int r = 0; r < CHUNK1_ROWS; r++) {
        for (int c = 0; c < CHUNK1_COLS; c++) {
            char ch = CHUNK1_MAP[r][c];
            int idx = r * CHUNK1_COLS + c;

            if (ch == '#' || ch == 'T' || ch == 'B' || ch == 'L') {
                tiles_out[idx] = TILE_SOLID;
            } else if (ch == 'P') {
                // Static 3-tile tall solid pillar block (rows 9, 10, 11)
                for (int pr = r; pr < r + 3 && pr < CHUNK1_ROWS; pr++) {
                    tiles_out[pr * CHUNK1_COLS + c] = TILE_SOLID;
                }
            } else if (ch == 'S') {
                spawn_out->x = (float)(c * TILE_SIZE);
                spawn_out->y = (float)((r + 1) * TILE_SIZE - PLAYER_HEIGHT);
            } else if (ch == 'F') {
                fan_pos = (Vector2){ (float)(c * TILE_SIZE), (float)(r * TILE_SIZE) };
            }
        }
    }

    float screen_w = 1280.0f;
    float screen_h = 720.0f;
    float map_h = (float)(CHUNK1_ROWS * TILE_SIZE);

    camera.zoom = screen_h / map_h;
    camera.offset = (Vector2){ screen_w * 0.35f, screen_h * 0.5f };
    camera.target = *spawn_out;
    camera.rotation = 0.0f;
}

void stage1_library_update(const player_t *p, float dt) {
    // Wind gust loop (4 frames in wind_2.png)
    wind_timer += dt;
    if (wind_timer >= 0.10f) {
        wind_timer = 0.0f;
        wind_frame = (wind_frame + 1) % 4;
    }

    // Lee run loop (11 frames in lee_run.png)
    float speed = fabsf(p->vx);
    if (p->on_ground && speed > 10.0f) {
        float frame_delay = p->running ? 0.06f : 0.10f;
        lee_timer += dt;
        if (lee_timer >= frame_delay) {
            lee_timer = 0.0f;
            lee_frame = (lee_frame + 1) % 11;
        }
    } else if (!p->on_ground) {
        lee_frame = 5;
    } else {
        lee_frame = 0;
        lee_timer = 0.0f;
    }

    // Smooth camera follow clamped to map bounds (accounting for zoom)
    camera.target.x += (p->x - camera.target.x) * 8.0f * dt;
    camera.target.y += (p->y - camera.target.y) * 6.0f * dt;

    float half_view_w = (1280.0f * 0.5f) / camera.zoom;
    float half_view_h = (720.0f * 0.5f) / camera.zoom;
    float map_w = (float)(CHUNK1_COLS * TILE_SIZE);
    float map_h = (float)(CHUNK1_ROWS * TILE_SIZE);

    camera.offset = (Vector2){ 1280.0f * 0.5f, 720.0f * 0.5f };

    if (map_w <= half_view_w * 2.0f) {
        camera.target.x = map_w * 0.5f;
    } else {
        if (camera.target.x < half_view_w) camera.target.x = half_view_w;
        if (camera.target.x > map_w - half_view_w) camera.target.x = map_w - half_view_w;
    }

    if (map_h <= half_view_h * 2.0f) {
        camera.target.y = map_h * 0.5f;
    } else {
        if (camera.target.y < half_view_h) camera.target.y = half_view_h;
        if (camera.target.y > map_h - half_view_h) camera.target.y = map_h - half_view_h;
    }
}

char stage1_library_get_char(int col, int row) {
    if (row < 0 || row >= CHUNK1_ROWS || col < 0 || col >= CHUNK1_COLS) {
        return '.';
    }
    return CHUNK1_MAP[row][col];
}

Camera2D stage1_library_get_camera(void) {
    return camera;
}

int stage1_library_get_lee_frame(void) {
    return lee_frame;
}

int stage1_library_get_wind_frame(void) {
    return wind_frame;
}

Vector2 stage1_library_get_fan_pos(void) {
    return fan_pos;
}
