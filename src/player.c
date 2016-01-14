#include <stdlib.h>
#include <SDL2/SDL_opengl.h>
#include "player.h"
#include "log.h"


Player* Player_new() {
    Player* self = calloc(1, sizeof(Player));
    return self;
}


void Player_rotate(Player *self, float inclination, float azimuth) {
    self->inclination += inclination;
    self->azimuth += azimuth;

    if (self->inclination >= 360.0f) {
        self->inclination -= 360.0f;
    }

    if (self->inclination < 0.0f) {
        self->inclination += 360.0f;
    }

    if (self->azimuth >= 360.0f) {
        self->azimuth -= 360.0f;
    }

    if (self->azimuth < 0.0f) {
        self->azimuth += 360.0f;
    }
}


void Player_move_camera(Player *self) {
    Player_rotate_camera(self);
    glTranslatef(-self->position.x, -self->position.y, -self->position.z);
}


void Player_rotate_camera(Player *self) {
    glRotatef(self->inclination, 0.0f, 0.0f, 1.0f);
    glRotatef(self->azimuth, 1.0f, 0.0f, 0.0f);
}


void Player_unrotate_camera(Player *self) {
    glRotatef(-self->azimuth, 1.0f, 0.0f, 0.0f);
    glRotatef(-self->inclination, 0.0f, 0.0f, 1.0f);
}


void Player_destroy(Player *self) {
    free(self);
}


