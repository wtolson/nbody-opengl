#include <stdlib.h>
#include "star.h"


float randomFloat() {
    return ((float) rand()) / ((float) RAND_MAX);
}


Vector randomVector() {
    return Vector_init(
        (2.0 * randomFloat()) - 1.0,
        (2.0 * randomFloat()) - 1.0,
        (2.0 * randomFloat()) - 1.0
    );
}


Star Star_random() {
    Star result = {
        .mass = randomFloat(),
        .position = randomVector(),
        .velocity = Vector_scale(randomVector(), 0.2),
    };
    return result;
}
