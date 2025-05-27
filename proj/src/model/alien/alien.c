#include "alien.h"

Alien *createAlien(int x, int y, int lives, Sprite *sprite) {
    Alien *alien = (Alien *)malloc(sizeof(Alien));
    if (alien == NULL) {
        return NULL; // Memory allocation failed
    }
    alien->x = x;
    alien->y = y;
    alien->lives = lives;
    alien->sprite = sprite;
    return alien;
}

void destroyAlien(Alien *alien) {
    if (alien != NULL) {
        if (alien->sprite != NULL) {
            destroy_sprite(alien->sprite);
        }
        free(alien);
    }
}

void drawAlien(Alien *alien) {
    if (alien != NULL && alien->sprite != NULL) {
        draw_sprite(alien->sprite, alien->x, alien->y);
    }
}

void alienMove(Alien *alien, int delta_x, int delta_y) {
    alien->x += delta_x;
    alien->y += delta_y;

    if (alien->x < 200) alien->x = 200;
    if (alien->x > 600 - alien->sprite->width) alien->x = 600 - alien->sprite->width;
    if (alien->y < 0) alien->y = 0;
    // PODE ALTERAR
    if (alien->y > 800 - alien->sprite->height) alien->y = 800 - alien->sprite->height;
}
