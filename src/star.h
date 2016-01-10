#ifndef _nbody_star_h
#define _nbody_star_h


#include "vector.h"


typedef struct {
    float mass;
    Vector position;
    Vector velocity;
} Star;


Star Star_random();


#endif
