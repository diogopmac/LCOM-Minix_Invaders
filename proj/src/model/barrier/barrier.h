#pragma once

#include <lcom/lcf.h>
#include "../../sprites/sprite.h"

typedef struct {
    int x;
    int y;
    int lives;
    int score;
    Sprite *sprite;
} Barrier;

Barrier *createBarrier(int x, int y);
void destroyBarrier(Barrier *barrier);
void drawBarrier(Barrier *barrier);
