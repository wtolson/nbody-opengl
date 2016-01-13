#pragma once

#include "vector.h"

typedef struct {
    Vector position;
} Camera;

Camera* Camera_new(void);
void Camera_translate(Camera *self, float x, float y, float z);
void Camera_reset(Camera *self);
void Camera_draw(Camera *self);
void Camera_destroy(Camera *self);
