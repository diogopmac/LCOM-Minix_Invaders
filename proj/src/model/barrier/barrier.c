#include "barrier.h"

Barrier *createBarrier(int x, int y, int lives, Sprite *sprite) {
    Barrier *barrier = (Barrier *)malloc(sizeof(Barrier));
    if (barrier == NULL) {
        return NULL; // Memory allocation failed
    }
    barrier->x = x;
    barrier->y = y;
    barrier->lives = lives;
    barrier->sprite = sprite;
    return barrier;
}

void destroyBarrier(Barrier *barrier) {
    if (barrier != NULL) {
        if (barrier->sprite != NULL) {
            destroy_sprite(barrier->sprite);
        }
        free(barrier);
    }
}

void drawBarrier(Barrier *barrier) {
    if (barrier != NULL && barrier->sprite != NULL) {
        draw_sprite(barrier->sprite, barrier->x, barrier->y);
    }
}