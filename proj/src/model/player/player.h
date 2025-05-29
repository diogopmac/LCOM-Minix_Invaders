#pragma once

#include <lcom/lcf.h>
#include "../../sprites/sprite.h"

typedef struct {
    int x;
    int y;
    int lives;
    int score;
    Sprite *sprite;
} Player;

Player *createPlayer(int x, int y, int lives, int score, Sprite *sprite);
void destroyPlayer(Player *player);
void drawPlayer(Player *player);

void playerMove(Player *player, int delta_x);
void playerDamage(Player *player);
