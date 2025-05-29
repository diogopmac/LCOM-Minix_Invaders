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

void (createGameSprites)(){
    airship = create_sprite(airship_xpm);
    p_projectile = create_sprite(airship_projectile_xpm);

    alien1 = create_sprite(alien1_xpm);
    alien2 = create_sprite(alien2_xpm);
    alien3 = create_sprite(alien3_xpm);
    alien_explosion = create_sprite(alien_explosion_xpm);

    barrier_st0 = create_sprite(stage0_xpm);
    barrier_st1 = create_sprite(stage1_xpm);
    barrier_st2 = create_sprite(stage2_xpm);
    barrier_st3 = create_sprite(stage3_xpm);
    // Outros sprites do jogo, inimigos, etc.
}

void (destroyGameSprites)() {
    destroy_sprite(airship);
    destroy_sprite(p_projectile);

    destroy_sprite(alien1);
    destroy_sprite(alien2);
    destroy_sprite(alien3);
    destroy_sprite(alien_explosion);

    destroy_sprite(barrier_st0);
    destroy_sprite(barrier_st1);
    destroy_sprite(barrier_st2);
    destroy_sprite(barrier_st3);
    // Outros sprites do jogo, inimigos, etc.
}
