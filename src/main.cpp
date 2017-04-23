#include <iostream>
#include <random>
#include <functional>
#include <ctime>
#include "tools/entitygenerator.hpp"
#include "tools/stopwatch.h"
#include "gjk/gjk.hpp"

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

    int countTrue = 0;
    int countFalse = 0;
    for(int j = 0; j < virtual_environment.GetEntities()->size(); j++){
        Entity e1 = virtual_environment.GetEntities()->at(j);
        for(int k = j + 1; k < virtual_environment.GetEntities()->size(); k++) {
            Entity e2 = virtual_environment.GetEntities()->at(k);
            bool hit = gjk::Run(e2, e1);
            if (hit)
                countTrue++;
            else
                countFalse++;
        }
    }

    std::cout << "Test Passed: " << countTrue << " times." << std::endl;
    std::cout << "Test Failed: " << countFalse << " times." << std::endl;

    return 0;
}