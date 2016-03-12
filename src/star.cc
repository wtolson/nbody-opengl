#include <stdlib.h>
#include <math.h>
#include <glm/gtc/random.hpp>
#include "star.h"


float randomFloat() {
    return ((float) rand()) / ((float) RAND_MAX);
}


Star Star::random() {
    Star star;
    star.mass = randomFloat();
    star.position = glm::sphericalRand(1.0f);
    star.velocity = glm::sphericalRand(0.2f);
    return star;
}


float* Star::load_texture() {
    float* texture = (float*) calloc(STAR_TEXTURE_SIZE * STAR_TEXTURE_SIZE, sizeof(float));
    float radius = ((float) STAR_TEXTURE_SIZE) / 2.0f;
    float sigma_2 = 8.0f;

    for (size_t i = 0; i < STAR_TEXTURE_SIZE; ++i) {
        for (size_t j = 0; j < STAR_TEXTURE_SIZE; ++j) {
            float x = ((float) i) - radius;
            float y = ((float) j) - radius;

            float exponent = ((x * x) / (2.0f * sigma_2)) + ((y * y) / (2.0f * sigma_2));
            float alpha = expf(-exponent);

            size_t index = i + (STAR_TEXTURE_SIZE * j);
            texture[index] = alpha;
        }
    }
    return texture;
}
