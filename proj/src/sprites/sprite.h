#pragma once

#include <lcom/lcf.h>

#include "../controllers/video/video.h"

#include "../img/mouse/cursor.xpm"
#include "../img/airship/airship.xpm"

typedef struct {
    uint32_t *colors;
    int width;
    int height;
} Sprite;

Sprite *cursor;
Sprite *airship;

Sprite * (create_sprite)(xpm_map_t xpm);
int (draw_sprite)(Sprite *sprite, uint16_t x, uint16_t y);
void (destroy_sprite)(Sprite *sprite);

void (createMenuSprites)();
void (destroyMenuSprites)();

void (createGameSprites)();
void (destroyGameSprites)();
