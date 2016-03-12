#pragma once

#include "math/vector3.h"

#define DEFAULT_FIELD_OF_VIEW 60.0f
#define DEFAULT_NEAR_PLANE 0.0001f
#define DEFAULT_FAR_PLANE 100.0f
#define DEFAULT_ASPECT_RATIO (4.0f / 3.0f)

typedef struct {
    Vector3 position;
    float horizontal_angle;
    float vertical_angle;
    float field_of_view;
    float near_plane;
    float far_plane;
    float aspect_ratio;
} Camera;


Camera* Camera_new(void);
