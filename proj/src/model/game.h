#pragma once

#include <lcom/lcf.h>
#include "../controllers/video/video.h"
#include "../controllers/kbc/mouse.h"
#include "../controllers/kbc/kbd.h"
#include "cursor/cursor.h"
#include "player/player.h"
#include "alien/alien.h"
#include "barrier/barrier.h"

typedef enum {
    GAME_STATE_MENU,
    GAME_STATE_PLAYING,
    GAME_STATE_PAUSED,
    GAME_STATE_GAME_OVER,
    EXIT_GAME
} GameState;

int game_loop();
void game_update();
void game_render();
