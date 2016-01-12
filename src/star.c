#include <stdlib.h>
#include "star.h"


float randomFloat() {
    return ((float) rand()) / ((float) RAND_MAX);
}

Vector randomVector() {
    return Vector_init(
        randomFloat(),
        randomFloat(),
        randomFloat()
    );
}



Star Star_random() {
    Star result = {
        .mass = randomFloat(),
        .position = randomVector(),
        .velocity = randomVector(),
    };
    return result;
}