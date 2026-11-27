#include "stage1_library_render.h"
#include "stage1_library.h"
#include "paths.h"
#include "raylib.h"

static Texture2D tex_wall;
static Texture2D tex_hanging_shelf;
static Texture2D tex_large_shelf;
static Texture2D tex_fan;
static Texture2D tex_wind;
static Texture2D tex_lee_run;
static Texture2D tex_pillar;

void stage1_library_render_init(void) {
    tex_wall          = LoadTexture(asset_path("sprites/block/wall_initial_design.png"));
    tex_hanging_shelf = LoadTexture(asset_path("sprites/block/hanging shelf.png"));
    tex_large_shelf   = LoadTexture(asset_path("sprites/block/shelf.png"));
    tex_fan           = LoadTexture(asset_path("sprites/block/fan.png"));
    tex_wind          = LoadTexture(asset_path("sprites/block/wind_2.png"));
    tex_lee_run       = LoadTexture(asset_path("sprites/effects/lee_run.png"));
    tex_pillar        = LoadTexture(asset_path("sprites/block/pillar.png"));
}

void stage1_library_render_world(void) {
    // 1. Solid Stone Blocks, Pillars & Hazard Pit
    for (int r = 0; r < CHUNK1_ROWS; r++) {
        for (int c = 0; c < CHUNK1_COLS; c++) {
            char ch = stage1_library_get_char(c, r);
            Rectangle dst = {
                (float)(c * TILE_SIZE),
                (float)(r * TILE_SIZE),
                (float)TILE_SIZE,
                (float)TILE_SIZE
            };

            if (ch == '#') {
                if (tex_wall.id > 0) {
                    Rectangle src = { 0, 0, (float)tex_wall.width, (float)tex_wall.height };
                    DrawTexturePro(tex_wall, src, dst, (Vector2){0, 0}, 0.0f, WHITE);
                } else {
                    DrawRectangleRec(dst, DARKGRAY);
                }
            } else if (ch == '^') {
                DrawRectangleRec(dst, Fade(RED, 0.8f));
                DrawRectangleLinesEx(dst, 2.0f, MAROON);
            } else if (ch == 'P') {
                // Static 1x3 upright pillar block using pillar.png
                float pil_w = (float)TILE_SIZE * 1.15f;
                float pil_h = (float)TILE_SIZE * 3.0f;
                Rectangle pil_dst = {
                    (float)(c * TILE_SIZE) - (pil_w - TILE_SIZE) * 0.5f,
                    (float)(r * TILE_SIZE),
                    pil_w,
                    pil_h
                };
                if (tex_pillar.id > 0) {
                    Rectangle pil_src = { 0.0f, 0.0f, (float)tex_pillar.width, (float)tex_pillar.height };
                    DrawTexturePro(tex_pillar, pil_src, pil_dst, (Vector2){0, 0}, 0.0f, WHITE);
                } else {
                    DrawRectangleRec(pil_dst, BEIGE);
                }
            }
        }
    }

    // 2. First Step: Hanging Shelf (4 tiles wide x 1 tile tall at col 6, row 11)
    Rectangle step_dst = {
        6.0f * TILE_SIZE,
        11.0f * TILE_SIZE,
        4.0f * TILE_SIZE,
        1.0f * TILE_SIZE
    };
    if (tex_hanging_shelf.id > 0) {
        Rectangle src = { 0, 0, (float)tex_hanging_shelf.width, (float)tex_hanging_shelf.height };
        DrawTexturePro(tex_hanging_shelf, src, step_dst, (Vector2){0, 0}, 0.0f, WHITE);
    } else {
        DrawRectangleRec(step_dst, (Color){ 160, 110, 60, 255 });
    }

    // 3. Large Center Shelf (6 tiles wide x 3 tiles tall at col 12, row 9)
    Rectangle shelf_dst = {
        12.0f * TILE_SIZE,
        9.0f * TILE_SIZE,
        6.0f * TILE_SIZE,
        3.0f * TILE_SIZE
    };
    if (tex_large_shelf.id > 0) {
        Rectangle src = { 0, 0, (float)tex_large_shelf.width, (float)tex_large_shelf.height };
        DrawTexturePro(tex_large_shelf, src, shelf_dst, (Vector2){0, 0}, 0.0f, WHITE);
    } else {
        DrawRectangleRec(shelf_dst, (Color){ 139, 90, 43, 255 });
    }

    // 4. Fan & Animated Wind Gust
    Vector2 fan_pos = stage1_library_get_fan_pos();
    float fan_h = (float)PLAYER_HEIGHT;
    float fan_w = (float)TILE_SIZE * 1.25f;

    if (tex_fan.id > 0) {
        Rectangle fan_src = { 0, 0, (float)tex_fan.width, (float)tex_fan.height };
        Rectangle fan_dst = { fan_pos.x, fan_pos.y, fan_w, fan_h };
        DrawTexturePro(tex_fan, fan_src, fan_dst, (Vector2){0, 0}, 0.0f, WHITE);
    }

    if (tex_wind.id > 0) {
        int wind_frame = stage1_library_get_wind_frame();
        float wf = (float)tex_wind.width / 4.0f;
        Rectangle wind_src = { wind_frame * wf, 0.0f, wf, (float)tex_wind.height };
        Rectangle wind_dst = {
            fan_pos.x + fan_w,
            fan_pos.y + (fan_h - TILE_SIZE) * 0.5f,
            TILE_SIZE * 2.5f,
            (float)TILE_SIZE
        };
        DrawTexturePro(tex_wind, wind_src, wind_dst, (Vector2){0, 0}, 0.0f, WHITE);
    }
}

void stage1_library_render_player(const player_t *p) {
    if (p->invulnerable_timer > 0.0f && ((int)(p->invulnerable_timer * 16.0f) % 2 == 0)) {
        return;
    }

    if (tex_lee_run.id > 0) {
        int lee_frame = stage1_library_get_lee_frame();
        float frame_w = (float)tex_lee_run.width / 11.0f;
        float frame_h = (float)tex_lee_run.height;

        Rectangle src = {
            lee_frame * frame_w,
            0.0f,
            frame_w * (float)p->facing,
            frame_h
        };

        float draw_w = (float)PLAYER_WIDTH * 1.4f;
        float draw_h = (float)PLAYER_HEIGHT * 1.15f;
        Rectangle dst = {
            p->x - (draw_w - PLAYER_WIDTH) * 0.5f,
            p->y - (draw_h - PLAYER_HEIGHT),
            draw_w,
            draw_h
        };

        DrawTexturePro(tex_lee_run, src, dst, (Vector2){0, 0}, 0.0f, WHITE);
    } else {
        DrawRectangle((int)p->x, (int)p->y, PLAYER_WIDTH, PLAYER_HEIGHT, MAROON);
    }
}

void stage1_library_render_cleanup(void) {
    UnloadTexture(tex_wall);
    UnloadTexture(tex_hanging_shelf);
    UnloadTexture(tex_large_shelf);
    UnloadTexture(tex_fan);
    UnloadTexture(tex_wind);
    UnloadTexture(tex_lee_run);
    UnloadTexture(tex_pillar);
}
