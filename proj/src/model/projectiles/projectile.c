#include "projectile.h"

Projectile *createProjectile(int x, int y, char type, Sprite *sprite) {
//Projectile *createProjectile(int x, int y, int velocity, Sprite *sprite) {
    Projectile *projectile = (Projectile *)malloc(sizeof(Projectile));
    if (projectile == NULL) {
        return NULL; // Memory allocation failed
    }
    projectile->x = x;
    projectile->y = y;
    projectile->type = type;
    //projectile->velocity = velocity;
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
