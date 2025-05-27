#pragma once

#include <lcom/lcf.h>
#include "../../sprites/sprite.h"

typedef struct {
    int x, y;
    Sprite *sprite;
} Cursor;


Cursor *createCursor(Sprite *sprite);
void (cursor_update_location)(Cursor *cursor, struct packet *mouse_packet);
int drawCursor(Cursor *cursor);
void destroyCursor(Cursor *cursor);
