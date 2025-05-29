#pragma once

#include <lcom/lcf.h>
#include "../../sprites/sprite.h"

typedef struct {
    int x;
    int y;
    char type; // 'A' for alien, 'P' for alien
    //int velocity; 
    Sprite *sprite;
} Projectile;

Projectile *createProjectile(int x, int y, char type, Sprite *sprite);
void destroyProjectile(Projectile *projectile);
void drawProjectile(Projectile *projectile);
void projectileMove(Projectile *projectile);
