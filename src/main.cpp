#include <iostream>
#include <ctime>
#include <cstdlib>

#include "pool_lib.hpp"
#include "rand_values.hpp"

int main () {
    unsigned int start_time =  clock();

    const size_t N = 32000000;
    const size_t K = 15000000;
    const size_t L = 22000000;
    const size_t M =  1900000;

    volatile float x = -1;

    many_pools<int, int> c{N};

    for (size_t i = 1; i <= N; ++i) {
        c.add_water (i, rand_water ());
    }

    for (size_t i = 1; i <= K; ++i) {
        c.connect (rand_pool (N), rand_pool (N));
    }

    for (size_t i = 1; i <= N; ++i) {
        x = c.water_in (i);
    }

    for (size_t i = 1; i <= L; ++i) {
        c.add_water (i, rand_water ());
    }

    for (size_t i = 1; i <= N; ++i) {
        x = c.water_in (i);
    }

    for (size_t i = 1; i <= M; ++i) {
        c.disconnect (rand_pool (N), rand_pool (N));
    }

    for (size_t i = 1; i <= L; ++i) {
        c.add_water (i, rand_water ());
    }

    for (size_t i = 1; i <= N; ++i) {
        x = c.water_in (i);
    }

    unsigned int end_time =  clock();

    std::cout << "time: " << static_cast <float> (end_time - start_time) / static_cast <float> (CLOCKS_PER_SEC) << std::endl;

    return 0;
}