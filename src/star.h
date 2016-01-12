#pragma once

#include "vector.h"

#define STAR_TEXTURE_SIZE 16

typedef struct {
    float mass;
    Vector position;
    Vector velocity;
} Star;

Star Star_random(void);
float* load_star_texture(void);
