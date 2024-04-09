#include <iostream>
#include <cstdio>

#include "pool_lib.hpp"

int main () {
    size_t n_pools = 3;

    many_pools<int> c{n_pools};

    c.add_water_in_pool (1, 10);
    c.add_water_in_pool (2, 20);
    c.add_water_in_pool (3, 50);

    c.water_volume_in_pool (1);
    c.water_volume_in_pool (2);
    c.water_volume_in_pool (3);

    c.connect_pools (1, 2);

    c.add_water_in_pool (1, 10);

    c.connect_pools (2, 3);

    c.destroy_pools_connection(1, 2);

    c.add_water_in_pool (2, 10);

    c.water_volume_in_pool (1);
    c.water_volume_in_pool (2);
    c.water_volume_in_pool (3);

    return 0;
}