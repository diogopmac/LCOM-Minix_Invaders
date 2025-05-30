#include "hud.h"

void draw_number(int number, int x, int y) {
    char buffer[12];
    snprintf(buffer, sizeof(buffer), "%d", number);
    
    int length = strlen(buffer);
    for (int i = 0; i < length; i++) {
        char digit = buffer[i];
        if (digit >= '0' && digit <= '9') {
            draw_sprite(get_digit_sprite(digit - '0'), x + i * (number_0->width + 3), y);
        }
    }
}

void drawHud(Player *player) {
    if (player == NULL) {
        return;
    }

    for (int i = 0; i < 3; i++) {
        if (i < player->lives) {
            draw_sprite(heart_life, 510 + i * (heart_life->width + 5), 590 - heart_life->height);
        } else {
            draw_sprite(heart_nolife, 510 + i * (heart_nolife->width + 5), 590 - heart_nolife->height);
        }
    }

    draw_number(player->score, 510, 10);
}
