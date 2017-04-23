#include <iostream>
#include <random>
#include <functional>
#include <ctime>
#include "tools/entitygenerator.hpp"
#include "tools/stopwatch.h"

#define NUMBER_OF_ENTITIES 10

int main() {
    /* virtual_environment will hold all the entities */
    VirtualEnvironment virtual_environment;

    /* Helper class for generating varying shapes, positions and sizes */
    EntityGenerator gen(100, 0);

    stop_watch watch;
    watch.start();
//    #pragma omp parallel for
    for (int i = 0; i < NUMBER_OF_ENTITIES; i++) {
        Entity cube = gen.GenerateCube();
        virtual_environment.AddEntity(cube);
        std::cout << cube << std::endl;
    }
    watch.stop();
    std::cout << watch << std::endl;

    return 0;
}