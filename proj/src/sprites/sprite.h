#pragma once

#include <lcom/lcf.h>

#include "../controllers/video/video.h"

#include "../img/mouse/cursor.xpm"
#include "../img/airship/airship.xpm"
#include "../img/airship/airship_projectile.xpm"
#include "../img/aliens/alien1.xpm"
#include "../img/aliens/alien2.xpm"
#include "../img/aliens/alien3.xpm"
#include "../img/aliens/alien_explosion.xpm"
#include "../img/barrier/stage0.xpm"
#include "../img/barrier/stage1.xpm"
#include "../img/barrier/stage2.xpm"
#include "../img/barrier/stage3.xpm"
#include "../img/aliens/alien_shoot.xpm"
#include "../img/symbols/heart_life.xpm"
#include "../img/symbols/heart_nolife.xpm"
#include "../img/symbols/n0.xpm"
#include "../img/symbols/n1.xpm"
#include "../img/symbols/n2.xpm"
#include "../img/symbols/n3.xpm"
#include "../img/symbols/n4.xpm"
#include "../img/symbols/n5.xpm"
#include "../img/symbols/n6.xpm"
#include "../img/symbols/n7.xpm"
#include "../img/symbols/n8.xpm"
#include "../img/symbols/n9.xpm"

typedef struct {
    uint32_t *colors;
    int width;
    int height;
} Sprite;

Sprite *cursor;
Sprite *airship;
Sprite *p_projectile;
Sprite *alien1;
Sprite *alien2;
Sprite *alien3;
Sprite *alien_explosion;
Sprite *a_projectile;
Sprite *barrier_st0;
Sprite *barrier_st1;
Sprite *barrier_st2;
Sprite *barrier_st3;
Sprite *heart_life;
Sprite *heart_nolife;
Sprite *number_0;
Sprite *number_1;
Sprite *number_2;
Sprite *number_3;
Sprite *number_4;
Sprite *number_5;
Sprite *number_6;
Sprite *number_7;
Sprite *number_8;
Sprite *number_9;

Sprite * (create_sprite)(xpm_map_t xpm);
int (draw_sprite)(Sprite *sprite, uint16_t x, uint16_t y);
void (destroy_sprite)(Sprite *sprite);

Sprite *get_digit_sprite(char digit);

void (createMenuSprites)();
void (destroyMenuSprites)();

void (createGameSprites)();
void (destroyGameSprites)();
