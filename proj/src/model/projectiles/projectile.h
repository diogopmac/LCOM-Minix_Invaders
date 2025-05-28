#pragma once

#include <lcom/lcf.h>
#include "../../sprites/sprite.h"

typedef struct {
    int x;
    int y;
    int velocity; 
    Sprite *sprite;
} Projectile;

Projectile *createProjectile(int x, int y, int velocity, Sprite *sprite);
void destroyProjectile(Projectile *projectile);
void drawProjectile(Projectile *projectile);
void projectileMove(Projectile *projectile, int delta_y);