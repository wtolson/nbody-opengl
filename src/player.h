#pragma once

#include "vector.h"

typedef struct {
    Vector position;
    Vector velocity;
    Vector acceleration;

    float inclination;
    float azimuth;
} Player;

Player* Player_new(void);
void Player_rotate(Player *self, float inclination, float azimuth);
void Player_move_camera(Player *self);
void Player_rotate_camera(Player *self);
void Player_unrotate_camera(Player *self);
void Player_destroy(Player *self);
