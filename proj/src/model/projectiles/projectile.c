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
    if (projectile != NULL && projectile->sprite != NULL) {
        draw_sprite(projectile->sprite, projectile->x, projectile->y);
    }
}

void projectileMove(Projectile *projectile, int delta_y) {
    projectile->y += delta_y;

    if (projectile->y < 0) projectile->y = 0;
    if (projectile->y > 600 - projectile->sprite->height) 
        projectile->y = 600 - projectile->sprite->height;
}
