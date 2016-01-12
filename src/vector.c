#include <math.h>
#include "vector.h"


Vector Vector_init(float x, float y, float z) {
    Vector result = {x, y, z};
    return result;
}


Vector Vector_add(Vector a, Vector b) {
    Vector result = {
        a.x + b.x,
        a.y + b.y,
        a.z + b.z,
    };
    return result;
}


Vector Vector_subtract(Vector a, Vector b) {
    Vector result = {
        a.x - b.x,
        a.y - b.y,
        a.z - b.z,
    };
    return result;
}


Vector Vector_scale(Vector self, float factor) {
    Vector result = {
        factor * self.x,
        factor * self.y,
        factor * self.z,
    };
    return result;

}


float Vector_dot(Vector a, Vector b) {
    return (a.x * b.x) + (a.y * b.y) + (a.z * b.z);
}


float Vector_mag(Vector self) {
    return sqrtf(Vector_dot(self, self));
}
