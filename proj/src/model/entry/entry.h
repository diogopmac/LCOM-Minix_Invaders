#pragma once

#include <lcom/lcf.h>
#include "../../sprites/sprite.h"

typedef struct {
    int x, y;
    bool selected;
    Sprite *sprite;
} Entry;

Entry *createEntry(int x, int y, bool selected, Sprite *sprite);
void destroyEntry(Entry *entry);
int drawEntry(Entry *entry);
void toggleEntry(Entry *entry, Sprite *sprite, Sprite *highlighted_sprite);
