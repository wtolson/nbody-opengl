#ifndef _nbody_vector_h
#define _nbody_vector_h


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


#endif
