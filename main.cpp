#include <iostream>
#include <cstdio>

#include "pool_lib.hpp"

int main () {
    size_t n_pools = 6;

    many_pools<int> c{n_pools};


    c.connect (1, 2);
    c.connect (2, 3);
    c.connect (3, 1);

    c.connect (3, 4);

    c.connect (4, 5);
    c.connect (4, 6);
    c.connect (5, 6);

    c.add_water (1, 6);
    c.show_volume_and_size_of_set(6);

    c.water_in (1);
    c.water_in (2);
    c.water_in (3);
    c.water_in (4);
    c.water_in (5);
    c.water_in (6);

    c.disconnect(3, 4);


    c.add_water (1, 6);
    c.show_volume_and_size_of_set(6);
    c.show_volume_and_size_of_set(7);

    c.water_in (1);
    c.water_in (2);
    c.water_in (3);
    c.water_in (4);
    c.water_in (5);
    c.water_in (6);

    return 0;
}