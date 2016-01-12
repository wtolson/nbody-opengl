#ifndef _nbody_star_h
#define _nbody_star_h


#include "vector.h"

#define STAR_TEXTURE_SIZE 16

typedef struct {
    float mass;
    Vector position;
    Vector velocity;
} Star;


Star Star_random(void);
float* load_star_texture(void);

#endif
