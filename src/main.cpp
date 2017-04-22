#include <iostream>
#include <random>
#include <functional>
#include <ctime>
#include "tools/entitygenerator.hpp"
#include "tools/stopwatch.h"
#include "gjk/gjk.hpp"

#define NUMBER_OF_ENTITIES 1000000

int main() {
    /* virtual_environment will hold all the entities */
    VirtualEnvironment virtual_environment;

    /* Helper class for generating varying shapes, positions and sizes */
    EntityGenerator gen(1000, 0);

    stop_watch watch;
    watch.start();
    #pragma omp parallel for
    for (int i = 0; i < NUMBER_OF_ENTITIES; i++) {
        Entity cube = gen.GenerateCube();
        virtual_environment.AddEntity(cube);
    }
    watch.stop();
    std::cout << watch << std::endl;

    Entity cube1 = entity::cube;
    Entity cube2 = entity::cube;
    bool hit = gjk::Run(cube1, cube2);
    std::cout << hit << std::endl;

    return 0;
}