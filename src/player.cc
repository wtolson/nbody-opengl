#include <stdlib.h>
#include <SDL2/SDL_opengl.h>
#include "player.h"
#include "log.h"




void Player::rotate(float inclination, float azimuth) {
    this->inclination += inclination;
    this->azimuth += azimuth;

    if (this->inclination >= 360.0f) {
        this->inclination -= 360.0f;
    }

    if (this->inclination < 0.0f) {
        this->inclination += 360.0f;
    }

    if (this->azimuth >= 360.0f) {
        this->azimuth -= 360.0f;
    }

    if (this->azimuth < 0.0f) {
        this->azimuth += 360.0f;
    }
}


void Player::move_camera() {
    this->rotate_camera();
    glTranslatef(-this->position.x, -this->position.y, -this->position.z);
}


void Player::rotate_camera() {
    glRotatef(this->inclination, 0.0f, 0.0f, 1.0f);
    glRotatef(this->azimuth, 1.0f, 0.0f, 0.0f);
}


void Player::unrotate_camera() {
    glRotatef(-this->azimuth, 1.0f, 0.0f, 0.0f);
    glRotatef(-this->inclination, 0.0f, 0.0f, 1.0f);
}


