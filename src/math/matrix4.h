#pragma once

#include "math/vector3.h"

#define MATRIX4_DIM 4
#define MATRIX4_SIZE (MATRIX4_DIM * MATRIX4_DIM)

typedef struct {
    float value[MATRIX4_SIZE];
} Matrix4;

Matrix4 Matrix4_identity(void);
Matrix4 Matrix4_add(Matrix4 a, Matrix4 b);
Matrix4 Matrix4_subtract(Matrix4 a, Matrix4 b);
Matrix4 Matrix4_multiply(Matrix4 a, Matrix4 b);
Matrix4 Matrix4_rotate(Matrix4 m, float angle, Vector3 axis);
