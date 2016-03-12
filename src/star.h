#pragma once

#include "math/vector3.h"

#define STAR_TEXTURE_SIZE 16

typedef struct {
    float mass;
    Vector3 position;
    Vector3 velocity;
} Star;

Star Star_random(void);
float* load_star_texture(void);
