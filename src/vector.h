#pragma once

#define log_vector(M, v, ...) printf(M "<%f %f %f>\n", ##__VA_ARGS__, v.x, v.y, v.z);

typedef struct {
    float x;
    float y;
    float z;
} Vector;

Vector Vector_init(float x, float y, float z);
Vector Vector_add(Vector a, Vector b);
Vector Vector_subtract(Vector a, Vector b);
Vector Vector_scale(Vector self, float factor);
float Vector_dot(Vector a, Vector b);
float Vector_mag(Vector self);
