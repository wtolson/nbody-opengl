#include <stdlib.h>
#include <SDL2/SDL_opengl.h>
#include "camera.h"


Camera* Camera_new() {
    Camera* self = calloc(1, sizeof(Camera));
    return self;
}


void Camera_translate(Camera *self, float x, float y, float z) {
    self->position.x += x;
    self->position.y += y;
    self->position.z += z;
}

void Camera_reset(Camera *self) {
    self->position = Vector_init(0.0f, 0.0f, 0.0f);
}

void Camera_draw(Camera *self) {
    glTranslatef(-self->position.x, -self->position.y, -self->position.z);
}

void Camera_destroy(Camera *self) {
    free(self);
}


