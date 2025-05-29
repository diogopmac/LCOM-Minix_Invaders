#include "projectile.h"

Projectile *createProjectile(int x, int y, char type, Sprite *sprite) {
    Projectile *projectile = (Projectile *)malloc(sizeof(Projectile));
    if (projectile == NULL) {
        return NULL;
    }
    projectile->x = x;
    projectile->y = y;
    projectile->type = type;
    projectile->sprite = sprite;
    projectile->active = true;
    return projectile;
}

void destroyProjectile(Projectile *projectile) {
    if (projectile != NULL) {
        if (projectile->sprite != NULL) {
            destroy_sprite(projectile->sprite);
        }
        free(projectile);
    }
}

void drawProjectile(Projectile *projectile) {
    if (projectile != NULL && projectile->active && projectile->sprite != NULL) {
        draw_sprite(projectile->sprite, projectile->x, projectile->y);
    }
}

void projectileMove(Projectile *projectile) {
    if (projectile == NULL) return;
    if(projectile->type == 'P') projectile->y -= 5;
    else if (projectile->type == 'A') projectile->y += 5;

    if (projectile->y < 0 || 
        projectile->y > 600 - projectile->sprite->height)
        projectile->active = false; 
}

bool checkCollision(Projectile *projectile, Alien *alien) {
  if (projectile->x < alien->x + alien->sprite->width &&
      projectile->x + projectile->sprite->width > alien->x &&
      projectile->y < alien->y + alien->sprite->height &&
      projectile->y + projectile->sprite->height > alien->y) {
    return true;
  }
  return false;
}
