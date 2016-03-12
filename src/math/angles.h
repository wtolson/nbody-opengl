#pragma once

#include <math.h>

#define PI acosf(-1.0f)
#define TWO_PI 2.0f * PI
#define PI_OVER_TWO PI / 2.0f

float degrees_to_radians(float angle) {
    return angle * PI / 180.f;
}

float radians_to_degrees(float angle) {
    return angle * 180.f / PI;
}
