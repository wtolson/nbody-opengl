#ifndef _nbody_h
#define _nbody_h


#include <stdbool.h>
#include "window.h"
#include "star.h"

#define NUM_STARS 512


typedef struct {
    Window* window;
    bool running;
    Star stars[NUM_STARS];
    GLuint star_texture;
} NBody;


NBody* NBody_new();
void NBody_run(NBody* self);
void NBody_destroy(NBody* self);


#endif
