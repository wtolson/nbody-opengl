#include <stdlib.h>
#include <math.h>
#include "star.h"


float randomFloat() {
    return ((float) rand()) / ((float) RAND_MAX);
}


Vector randomVector() {
    return Vector_init(
        (2.0f * randomFloat()) - 1.0f,
        (2.0f * randomFloat()) - 1.0f,
        (2.0f * randomFloat()) - 1.0f
    );
}


Star Star_random() {
    Star result = {
        .mass = randomFloat(),
        .position = randomVector(),
        .velocity = Vector_scale(randomVector(), 0.2f),
    };
    return result;
}


float* load_star_texture() {
    float* texture = calloc(STAR_TEXTURE_SIZE * STAR_TEXTURE_SIZE, sizeof(float));
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
