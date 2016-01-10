#include "nbody.h"


int main(int argc, char* args[]) {
    NBody* nbody = NBody_new();
    if (nbody == NULL) {
        return -1;
    }

    NBody_run(nbody);
    NBody_destroy(nbody);

    return 0;
}
