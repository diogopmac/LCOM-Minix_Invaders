#pragma once

#include <lcom/lcf.h>
#include "../../sprites/sprite.h"
#include "../alien/alien.h"
#include "../barrier/barrier.h"
#include "../player/player.h"

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
bool checkCollisionAlien(Projectile *projectile, Alien *alien);
bool checkCollisionBarrier(Projectile *projectile, Barrier *barrier);
bool checkCollisionPlayer(Projectile *projectile, Player *player);
