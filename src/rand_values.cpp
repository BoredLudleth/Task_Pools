#include "rand_values.hpp"

float rand_water () {
    return rand() % 500 + 1;
}

int rand_pool (int N) {
    return rand() % N + 1;
}
