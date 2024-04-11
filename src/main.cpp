#include <iostream>
#include <cstdio>
#include <ctime>

#include "pool_lib.hpp"

int main () {
    unsigned int start_time =  clock();

    size_t N = 32000000;
    size_t K = 15000000;
    size_t L = 22000000;
    size_t M =  1900000;

    many_pools<int> c{N};

    for (int i = 1; i <= N; ++i) {
        c.add_water (i, rand() % 500 + 1);
    }

    for (int i = 1; i <= K; ++i) {
        c.connect (rand() % N + 1, rand() % N + 1);
    }

    for (int i = 1; i <= N; ++i) {
        c.water_in (i);
    }

    for (int i = 1; i <= L; ++i) {
        c.add_water (i, rand() % 500 + 1);
    }

    for (int i = 1; i <= N; ++i) {
        c.water_in (i);
    }

    for (int i = 1; i <= M; ++i) {
        c.disconnect (rand() % N + 1, rand() % N + 1);
    }

    for (int i = 1; i <= L; ++i) {
        c.add_water (i, rand() % 500 + 1);
    }

    for (int i = 1; i <= N; ++i) {
        c.water_in (i);
    }

    unsigned int end_time =  clock();

    std::cout << "time: " << static_cast <float> (end_time - start_time) / static_cast <float> (CLOCKS_PER_SEC) << std::endl;

    return 0;
}