#include "barrier.h"

Barrier *createBarrier(int x, int y) {
    Barrier *barrier = (Barrier *)malloc(sizeof(Barrier));
    if (barrier == NULL) {
        return NULL; // Memory allocation failed
    }
    barrier->x = x;
    barrier->y = y;
    barrier->lives = 4;
    barrier->sprite = barrier_st0;
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

void damageBarrier(Barrier *barrier) {
    if (barrier != NULL) {
        barrier->lives--;
        if (barrier->lives <= 0) {
            destroyBarrier(barrier);
        }

    }
}
