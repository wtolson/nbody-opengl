#pragma once

#include <glm/vec3.hpp>

#define STAR_TEXTURE_SIZE 16

class Star {
public:
    static Star random(void);
    static float* load_texture(void);

    float mass;
    glm::vec3 position;
    glm::vec3 velocity;
};
