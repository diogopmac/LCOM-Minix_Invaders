#pragma once

#include <lcom/lcf.h>

typedef struct {
    uint8_t *colors;
    int width;
    int height;
}

Sprite * (create_sprite)(xpm_map_t xpm);
void (destroy_sprite)(Sprite *sprite);