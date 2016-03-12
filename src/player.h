#pragma once

#include <glm/vec3.hpp>

class Player {
public:
    void rotate(float inclination, float azimuth);
    void move_camera();
    void rotate_camera();
    void unrotate_camera();

    glm::vec3 position;
    glm::vec3 velocity;
    glm::vec3 acceleration;

private:

    float inclination;
    float azimuth;
};
