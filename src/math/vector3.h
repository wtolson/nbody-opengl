#pragma once

#define log_vector3(M, v, ...) printf(M "<%f %f %f>\n", ##__VA_ARGS__, v.x, v.y, v.z);

typedef struct {
    float x;
    float y;
    float z;
} Vector3;

Vector3 Vector3_init(float x, float y, float z);
Vector3 Vector3_add(Vector3 a, Vector3 b);
Vector3 Vector3_subtract(Vector3 a, Vector3 b);
Vector3 Vector3_scale(Vector3 v, float factor);
Vector3 Vector3_normalize(Vector3 v);
float Vector3_dot(Vector3 a, Vector3 b);
float Vector3_magnitude(Vector3 v);
