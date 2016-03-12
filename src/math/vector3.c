#include <math.h>
#include "math/vector3.h"


Vector3 Vector3_init(float x, float y, float z) {
    return (Vector3) {x, y, z};
}


Vector3 Vector3_add(Vector3 a, Vector3 b) {
    return (Vector3) {
        a.x + b.x,
        a.y + b.y,
        a.z + b.z,
    };
}


Vector3 Vector3_subtract(Vector3 a, Vector3 b) {
    return (Vector3) {
        a.x - b.x,
        a.y - b.y,
        a.z - b.z,
    };
}


Vector3 Vector3_scale(Vector3 v, float factor) {
    return (Vector3) {
        factor * v.x,
        factor * v.y,
        factor * v.z,
    };

}


Vector3 Vector3_normalize(Vector3 v) {
    const float magnitude = Vector3_magnitude(v);
    return Vector3_scale(v, 1.0f / magnitude);
}


float Vector3_dot(Vector3 a, Vector3 b) {
    return (a.x * b.x) + (a.y * b.y) + (a.z * b.z);
}


float Vector3_magnitude(Vector3 v) {
    return sqrtf(Vector3_dot(v, v));
}

