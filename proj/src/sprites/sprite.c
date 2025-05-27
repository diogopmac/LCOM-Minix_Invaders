#include "sprite.h"

Sprite * (create_sprite)(xpm_map_t xpm) {
    Sprite *sprite = (Sprite *) malloc(sizeof(Sprite));
    if (sprite == NULL) {
        return NULL; // Memory allocation failed
    }

    xpm_image_t loaded_xpm;
    sprite->colors = (uint32_t*) xpm_load(xpm, XPM_8_8_8_8, &loaded_xpm);
    if (sprite->colors == NULL) {
        free(sprite);
        return NULL;
    }

    sprite->width = loaded_xpm.width;
    sprite->height = loaded_xpm.height;

    return sprite;
}

int (draw_sprite)(Sprite *sprite, uint16_t x, uint16_t y) {
    for (int i = 0; i < sprite->height; i++) {
        for (int j = 0; j < sprite->width; j++) {
            uint32_t color = sprite->colors[i * sprite->width + j];
            if (vg_draw_pixel(x + j, y + i, color) != 0) {
                return 1; // Error drawing pixel
            }
        }
    }

    return 0; // Success
}

void (destroy_sprite)(Sprite *sprite) {
    if (sprite != NULL) {
        if (sprite->colors != NULL) {
            free(sprite->colors);
        }
        free(sprite);
    }
}

void (createMenuSprites)() {
    cursor = create_sprite(cursor_xpm);
    // Titulo, botões, etc.
}

void (destroyMenuSprites)() {
    destroy_sprite(cursor);
    // Titulo, botões, etc.
}
