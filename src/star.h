#pragma once

#include "vector.h"

#define STAR_TEXTURE_SIZE 16

class Star {
public:
    static Star random(void);
    static float* load_texture(void);

    float mass;
    Vector position;
    Vector velocity;
};
