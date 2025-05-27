#pragma once

#include <lcom/lcf.h>
#include "../../sprites/sprite.h"

typedef struct {
    int x;
    int y;
    int lives;
    Sprite *sprite;
} Alien;

Alien *createAlien(int x, int y, int lives, Sprite *sprite);
void destroyAlien(Alien *alien);
void drawAlien(Alien *alien);
// 0 - left, 1 - right, 2 - down
void alienMove(Alien *alien, int direction);

