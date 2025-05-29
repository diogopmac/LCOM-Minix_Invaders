#pragma once

#include <lcom/lcf.h>
#include "../../sprites/sprite.h"
#include "../alien/alien.h"

typedef struct {
    int x;
    int y;
    char type; // 'A' for alien, 'P' for alien
    //int velocity; 
    Sprite *sprite;
    bool active;
} Projectile;

Projectile *createProjectile(int x, int y, char type, Sprite *sprite);
void destroyProjectile(Projectile *projectile);
void drawProjectile(Projectile *projectile);
void projectileMove(Projectile *projectile);
bool checkCollision(Projectile *projectile, Alien *alien);
