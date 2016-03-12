#pragma once

#include "vector.h"

class Player {
public:
    void rotate(float inclination, float azimuth);
    void move_camera();
    void rotate_camera();
    void unrotate_camera();

    Vector position;
    Vector velocity;
    Vector acceleration;

private:

    float inclination;
    float azimuth;
};
