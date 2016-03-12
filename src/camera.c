#include <stdlib.h>
#include "math/angles.h"
#include "math/matrix4.h"
#include "camera.h"


Camera* Camera_new() {
    Camera* self = calloc(1, sizeof(Camera));
    self->field_of_view = DEFAULT_FIELD_OF_VIEW;
    self->near_plane = DEFAULT_NEAR_PLANE;
    self->far_plane = DEFAULT_FAR_PLANE;
    self->aspect_ratio = DEFAULT_ASPECT_RATIO;
    return self;
}


void Camera_offset_position(Camera* self, Vector3 offset) {
    self->position = Vector3_add(self->position, offset);
}


Matrix4 Camera_orientation(Camera* self) {
    Matrix4 orientation = Matrix4_identity();
    orientation = Matrix4_rotate(orientation, degrees_to_radians(self->vertical_angle), Vector3_init(1, 0, 0));
    orientation = Matrix4_rotate(orientation, degrees_to_radians(self->horizontal_angle), Vector3_init(0, 1, 0));
    return orientation;
}
