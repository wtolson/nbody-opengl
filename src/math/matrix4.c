#include <math.h>
#include "math/matrix4.h"


#define MAT4_INDEX(i, j) (MATRIX4_DIM * i) + j
#define MAT4_VALUE(m, i, j) m.value[MAT4_INDEX(i, j)]


Matrix4 Matrix4_identity() {
    Matrix4 result = {{0.0f}};
    MAT4_VALUE(result, 0, 0) = 1.0f;
    MAT4_VALUE(result, 1, 1) = 1.0f;
    MAT4_VALUE(result, 2, 2) = 1.0f;
    MAT4_VALUE(result, 3, 3) = 1.0f;
    return result;
}


Matrix4 Matrix4_add(Matrix4 a, Matrix4 b) {
    Matrix4 result;

    MAT4_VALUE(result, 0, 0) = MAT4_VALUE(a, 0, 0) + MAT4_VALUE(b, 0, 0);
    MAT4_VALUE(result, 0, 1) = MAT4_VALUE(a, 0, 1) + MAT4_VALUE(b, 0, 1);
    MAT4_VALUE(result, 0, 2) = MAT4_VALUE(a, 0, 2) + MAT4_VALUE(b, 0, 2);
    MAT4_VALUE(result, 0, 3) = MAT4_VALUE(a, 0, 3) + MAT4_VALUE(b, 0, 3);

    MAT4_VALUE(result, 1, 0) = MAT4_VALUE(a, 1, 0) + MAT4_VALUE(b, 1, 0);
    MAT4_VALUE(result, 1, 1) = MAT4_VALUE(a, 1, 1) + MAT4_VALUE(b, 1, 1);
    MAT4_VALUE(result, 1, 2) = MAT4_VALUE(a, 1, 2) + MAT4_VALUE(b, 1, 2);
    MAT4_VALUE(result, 1, 3) = MAT4_VALUE(a, 1, 3) + MAT4_VALUE(b, 1, 3);

    MAT4_VALUE(result, 2, 0) = MAT4_VALUE(a, 2, 0) + MAT4_VALUE(b, 2, 0);
    MAT4_VALUE(result, 2, 1) = MAT4_VALUE(a, 2, 1) + MAT4_VALUE(b, 2, 1);
    MAT4_VALUE(result, 2, 2) = MAT4_VALUE(a, 2, 2) + MAT4_VALUE(b, 2, 2);
    MAT4_VALUE(result, 2, 3) = MAT4_VALUE(a, 2, 3) + MAT4_VALUE(b, 2, 3);

    MAT4_VALUE(result, 3, 0) = MAT4_VALUE(a, 3, 0) + MAT4_VALUE(b, 3, 0);
    MAT4_VALUE(result, 3, 1) = MAT4_VALUE(a, 3, 1) + MAT4_VALUE(b, 3, 1);
    MAT4_VALUE(result, 3, 2) = MAT4_VALUE(a, 3, 2) + MAT4_VALUE(b, 3, 2);
    MAT4_VALUE(result, 3, 3) = MAT4_VALUE(a, 3, 3) + MAT4_VALUE(b, 3, 3);

    return result;
}


Matrix4 Matrix4_subtract(Matrix4 a, Matrix4 b) {
    Matrix4 result;

    MAT4_VALUE(result, 0, 0) = MAT4_VALUE(a, 0, 0) - MAT4_VALUE(b, 0, 0);
    MAT4_VALUE(result, 0, 1) = MAT4_VALUE(a, 0, 1) - MAT4_VALUE(b, 0, 1);
    MAT4_VALUE(result, 0, 2) = MAT4_VALUE(a, 0, 2) - MAT4_VALUE(b, 0, 2);
    MAT4_VALUE(result, 0, 3) = MAT4_VALUE(a, 0, 3) - MAT4_VALUE(b, 0, 3);

    MAT4_VALUE(result, 1, 0) = MAT4_VALUE(a, 1, 0) - MAT4_VALUE(b, 1, 0);
    MAT4_VALUE(result, 1, 1) = MAT4_VALUE(a, 1, 1) - MAT4_VALUE(b, 1, 1);
    MAT4_VALUE(result, 1, 2) = MAT4_VALUE(a, 1, 2) - MAT4_VALUE(b, 1, 2);
    MAT4_VALUE(result, 1, 3) = MAT4_VALUE(a, 1, 3) - MAT4_VALUE(b, 1, 3);

    MAT4_VALUE(result, 2, 0) = MAT4_VALUE(a, 2, 0) - MAT4_VALUE(b, 2, 0);
    MAT4_VALUE(result, 2, 1) = MAT4_VALUE(a, 2, 1) - MAT4_VALUE(b, 2, 1);
    MAT4_VALUE(result, 2, 2) = MAT4_VALUE(a, 2, 2) - MAT4_VALUE(b, 2, 2);
    MAT4_VALUE(result, 2, 3) = MAT4_VALUE(a, 2, 3) - MAT4_VALUE(b, 2, 3);

    MAT4_VALUE(result, 3, 0) = MAT4_VALUE(a, 3, 0) - MAT4_VALUE(b, 3, 0);
    MAT4_VALUE(result, 3, 1) = MAT4_VALUE(a, 3, 1) - MAT4_VALUE(b, 3, 1);
    MAT4_VALUE(result, 3, 2) = MAT4_VALUE(a, 3, 2) - MAT4_VALUE(b, 3, 2);
    MAT4_VALUE(result, 3, 3) = MAT4_VALUE(a, 3, 3) - MAT4_VALUE(b, 3, 3);

    return result;
}


Matrix4 Matrix4_multiply(Matrix4 a, Matrix4 b) {
    Matrix4 result;

    MAT4_VALUE(result, 0, 0) = (
        (MAT4_VALUE(a, 0, 0) * MAT4_VALUE(b, 0, 0)) +
        (MAT4_VALUE(a, 0, 1) * MAT4_VALUE(b, 1, 0)) +
        (MAT4_VALUE(a, 0, 2) * MAT4_VALUE(b, 2, 0)) +
        (MAT4_VALUE(a, 0, 3) * MAT4_VALUE(b, 3, 0))
    );

    MAT4_VALUE(result, 0, 1) = (
        (MAT4_VALUE(a, 0, 0) * MAT4_VALUE(b, 0, 1)) +
        (MAT4_VALUE(a, 0, 1) * MAT4_VALUE(b, 1, 1)) +
        (MAT4_VALUE(a, 0, 2) * MAT4_VALUE(b, 2, 1)) +
        (MAT4_VALUE(a, 0, 3) * MAT4_VALUE(b, 3, 1))
    );

    MAT4_VALUE(result, 0, 2) = (
        (MAT4_VALUE(a, 0, 0) * MAT4_VALUE(b, 0, 2)) +
        (MAT4_VALUE(a, 0, 1) * MAT4_VALUE(b, 1, 2)) +
        (MAT4_VALUE(a, 0, 2) * MAT4_VALUE(b, 2, 2)) +
        (MAT4_VALUE(a, 0, 3) * MAT4_VALUE(b, 3, 2))
    );

    MAT4_VALUE(result, 0, 3) = (
        (MAT4_VALUE(a, 0, 0) * MAT4_VALUE(b, 0, 3)) +
        (MAT4_VALUE(a, 0, 1) * MAT4_VALUE(b, 1, 3)) +
        (MAT4_VALUE(a, 0, 2) * MAT4_VALUE(b, 2, 3)) +
        (MAT4_VALUE(a, 0, 3) * MAT4_VALUE(b, 3, 3))
    );

    MAT4_VALUE(result, 1, 0) = (
        (MAT4_VALUE(a, 1, 0) * MAT4_VALUE(b, 0, 0)) +
        (MAT4_VALUE(a, 1, 1) * MAT4_VALUE(b, 1, 0)) +
        (MAT4_VALUE(a, 1, 2) * MAT4_VALUE(b, 2, 0)) +
        (MAT4_VALUE(a, 1, 3) * MAT4_VALUE(b, 3, 0))
    );

    MAT4_VALUE(result, 1, 1) = (
        (MAT4_VALUE(a, 1, 0) * MAT4_VALUE(b, 0, 1)) +
        (MAT4_VALUE(a, 1, 1) * MAT4_VALUE(b, 1, 1)) +
        (MAT4_VALUE(a, 1, 2) * MAT4_VALUE(b, 2, 1)) +
        (MAT4_VALUE(a, 1, 3) * MAT4_VALUE(b, 3, 1))
    );

    MAT4_VALUE(result, 1, 2) = (
        (MAT4_VALUE(a, 1, 0) * MAT4_VALUE(b, 0, 2)) +
        (MAT4_VALUE(a, 1, 1) * MAT4_VALUE(b, 1, 2)) +
        (MAT4_VALUE(a, 1, 2) * MAT4_VALUE(b, 2, 2)) +
        (MAT4_VALUE(a, 1, 3) * MAT4_VALUE(b, 3, 2))
    );

    MAT4_VALUE(result, 1, 3) = (
        (MAT4_VALUE(a, 1, 0) * MAT4_VALUE(b, 0, 3)) +
        (MAT4_VALUE(a, 1, 1) * MAT4_VALUE(b, 1, 3)) +
        (MAT4_VALUE(a, 1, 2) * MAT4_VALUE(b, 2, 3)) +
        (MAT4_VALUE(a, 1, 3) * MAT4_VALUE(b, 3, 3))
    );

    MAT4_VALUE(result, 2, 0) = (
        (MAT4_VALUE(a, 2, 0) * MAT4_VALUE(b, 0, 0)) +
        (MAT4_VALUE(a, 2, 1) * MAT4_VALUE(b, 1, 0)) +
        (MAT4_VALUE(a, 2, 2) * MAT4_VALUE(b, 2, 0)) +
        (MAT4_VALUE(a, 2, 3) * MAT4_VALUE(b, 3, 0))
    );

    MAT4_VALUE(result, 2, 1) = (
        (MAT4_VALUE(a, 2, 0) * MAT4_VALUE(b, 0, 1)) +
        (MAT4_VALUE(a, 2, 1) * MAT4_VALUE(b, 1, 1)) +
        (MAT4_VALUE(a, 2, 2) * MAT4_VALUE(b, 2, 1)) +
        (MAT4_VALUE(a, 2, 3) * MAT4_VALUE(b, 3, 1))
    );

    MAT4_VALUE(result, 2, 2) = (
        (MAT4_VALUE(a, 2, 0) * MAT4_VALUE(b, 0, 2)) +
        (MAT4_VALUE(a, 2, 1) * MAT4_VALUE(b, 1, 2)) +
        (MAT4_VALUE(a, 2, 2) * MAT4_VALUE(b, 2, 2)) +
        (MAT4_VALUE(a, 2, 3) * MAT4_VALUE(b, 3, 2))
    );

    MAT4_VALUE(result, 2, 3) = (
        (MAT4_VALUE(a, 2, 0) * MAT4_VALUE(b, 0, 3)) +
        (MAT4_VALUE(a, 2, 1) * MAT4_VALUE(b, 1, 3)) +
        (MAT4_VALUE(a, 2, 2) * MAT4_VALUE(b, 2, 3)) +
        (MAT4_VALUE(a, 2, 3) * MAT4_VALUE(b, 3, 3))
    );

    MAT4_VALUE(result, 3, 0) = (
        (MAT4_VALUE(a, 3, 0) * MAT4_VALUE(b, 0, 0)) +
        (MAT4_VALUE(a, 3, 1) * MAT4_VALUE(b, 1, 0)) +
        (MAT4_VALUE(a, 3, 2) * MAT4_VALUE(b, 2, 0)) +
        (MAT4_VALUE(a, 3, 3) * MAT4_VALUE(b, 3, 0))
    );

    MAT4_VALUE(result, 3, 1) = (
        (MAT4_VALUE(a, 3, 0) * MAT4_VALUE(b, 0, 1)) +
        (MAT4_VALUE(a, 3, 1) * MAT4_VALUE(b, 1, 1)) +
        (MAT4_VALUE(a, 3, 2) * MAT4_VALUE(b, 2, 1)) +
        (MAT4_VALUE(a, 3, 3) * MAT4_VALUE(b, 3, 1))
    );

    MAT4_VALUE(result, 3, 2) = (
        (MAT4_VALUE(a, 3, 0) * MAT4_VALUE(b, 0, 2)) +
        (MAT4_VALUE(a, 3, 1) * MAT4_VALUE(b, 1, 2)) +
        (MAT4_VALUE(a, 3, 2) * MAT4_VALUE(b, 2, 2)) +
        (MAT4_VALUE(a, 3, 3) * MAT4_VALUE(b, 3, 2))
    );

    MAT4_VALUE(result, 3, 3) = (
        (MAT4_VALUE(a, 3, 0) * MAT4_VALUE(b, 0, 3)) +
        (MAT4_VALUE(a, 3, 1) * MAT4_VALUE(b, 1, 3)) +
        (MAT4_VALUE(a, 3, 2) * MAT4_VALUE(b, 2, 3)) +
        (MAT4_VALUE(a, 3, 3) * MAT4_VALUE(b, 3, 3))
    );

    return result;
}


Matrix4 Matrix4_rotate(Matrix4 m, float angle, Vector3 axis) {
    const float cos_angle = cosf(angle);
    const float sin_angle = sinf(angle);

    axis = Vector3_normalize(axis);
    Vector3 cos_axis = Vector3_scale(axis, cos_angle);

    Matrix4 rotate;

    MAT4_VALUE(rotate, 0, 0) = cos_angle + cos_axis.x * axis.x;
    MAT4_VALUE(rotate, 0, 1) = cos_axis.x * axis.y + sin_angle * axis.z;
    MAT4_VALUE(rotate, 0, 2) = cos_axis.x * axis.z - sin_angle * axis.y;
    MAT4_VALUE(rotate, 1, 0) = cos_axis.y * axis.x - sin_angle * axis.z;
    MAT4_VALUE(rotate, 1, 1) = cos_angle + cos_axis.y * axis.y;
    MAT4_VALUE(rotate, 1, 2) = cos_axis.y * axis.z + sin_angle * axis.x;
    MAT4_VALUE(rotate, 2, 0) = cos_axis.z * axis.x + sin_angle * axis.y;
    MAT4_VALUE(rotate, 2, 1) = cos_axis.z * axis.y - sin_angle * axis.x;
    MAT4_VALUE(rotate, 2, 2) = cos_angle + cos_axis.z * axis.z;

    Matrix4 result;

    MAT4_VALUE(result, 0, 0) = MAT4_VALUE(m, 0, 0) * MAT4_VALUE(rotate, 0, 0) + MAT4_VALUE(m, 1, 0) * MAT4_VALUE(rotate, 0, 1) + MAT4_VALUE(m, 2, 0) * MAT4_VALUE(rotate, 0, 2);
    MAT4_VALUE(result, 0, 1) = MAT4_VALUE(m, 0, 1) * MAT4_VALUE(rotate, 0, 0) + MAT4_VALUE(m, 1, 1) * MAT4_VALUE(rotate, 0, 1) + MAT4_VALUE(m, 2, 1) * MAT4_VALUE(rotate, 0, 2);
    MAT4_VALUE(result, 0, 2) = MAT4_VALUE(m, 0, 2) * MAT4_VALUE(rotate, 0, 0) + MAT4_VALUE(m, 1, 2) * MAT4_VALUE(rotate, 0, 1) + MAT4_VALUE(m, 2, 2) * MAT4_VALUE(rotate, 0, 2);
    MAT4_VALUE(result, 0, 3) = MAT4_VALUE(m, 0, 3) * MAT4_VALUE(rotate, 0, 0) + MAT4_VALUE(m, 1, 3) * MAT4_VALUE(rotate, 0, 1) + MAT4_VALUE(m, 2, 3) * MAT4_VALUE(rotate, 0, 2);

    MAT4_VALUE(result, 1, 0) = MAT4_VALUE(m, 0, 0) * MAT4_VALUE(rotate, 1, 0) + MAT4_VALUE(m, 1, 0) * MAT4_VALUE(rotate, 1, 1) + MAT4_VALUE(m, 2, 0) * MAT4_VALUE(rotate, 1, 2);
    MAT4_VALUE(result, 1, 1) = MAT4_VALUE(m, 0, 1) * MAT4_VALUE(rotate, 1, 0) + MAT4_VALUE(m, 1, 1) * MAT4_VALUE(rotate, 1, 1) + MAT4_VALUE(m, 2, 1) * MAT4_VALUE(rotate, 1, 2);
    MAT4_VALUE(result, 1, 2) = MAT4_VALUE(m, 0, 2) * MAT4_VALUE(rotate, 1, 0) + MAT4_VALUE(m, 1, 2) * MAT4_VALUE(rotate, 1, 1) + MAT4_VALUE(m, 2, 2) * MAT4_VALUE(rotate, 1, 2);
    MAT4_VALUE(result, 1, 3) = MAT4_VALUE(m, 0, 3) * MAT4_VALUE(rotate, 1, 0) + MAT4_VALUE(m, 1, 3) * MAT4_VALUE(rotate, 1, 1) + MAT4_VALUE(m, 2, 3) * MAT4_VALUE(rotate, 1, 2);

    MAT4_VALUE(result, 2, 0) = MAT4_VALUE(m, 0, 0) * MAT4_VALUE(rotate, 2, 0) + MAT4_VALUE(m, 1, 0) * MAT4_VALUE(rotate, 2, 1) + MAT4_VALUE(m, 2, 0) * MAT4_VALUE(rotate, 2, 2);
    MAT4_VALUE(result, 2, 1) = MAT4_VALUE(m, 0, 1) * MAT4_VALUE(rotate, 2, 0) + MAT4_VALUE(m, 1, 1) * MAT4_VALUE(rotate, 2, 1) + MAT4_VALUE(m, 2, 1) * MAT4_VALUE(rotate, 2, 2);
    MAT4_VALUE(result, 2, 2) = MAT4_VALUE(m, 0, 2) * MAT4_VALUE(rotate, 2, 0) + MAT4_VALUE(m, 1, 2) * MAT4_VALUE(rotate, 2, 1) + MAT4_VALUE(m, 2, 2) * MAT4_VALUE(rotate, 2, 2);
    MAT4_VALUE(result, 2, 3) = MAT4_VALUE(m, 0, 3) * MAT4_VALUE(rotate, 2, 0) + MAT4_VALUE(m, 1, 3) * MAT4_VALUE(rotate, 2, 1) + MAT4_VALUE(m, 2, 3) * MAT4_VALUE(rotate, 2, 2);

    MAT4_VALUE(result, 3, 0) = MAT4_VALUE(m, 3, 0);
    MAT4_VALUE(result, 3, 1) = MAT4_VALUE(m, 3, 1);
    MAT4_VALUE(result, 3, 2) = MAT4_VALUE(m, 3, 2);
    MAT4_VALUE(result, 3, 3) = MAT4_VALUE(m, 3, 3);

    return result;
}
