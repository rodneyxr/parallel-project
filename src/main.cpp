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

#if 1
    stop_watch watch;
    watch.start();
    #pragma omp parallel for
    for (int i = 0; i < NUMBER_OF_ENTITIES; i++) {
        Entity cube = gen.GenerateCube();
        virtual_environment.AddEntity(cube);
    }
    watch.stop();
    std::cout << watch << std::endl;
#endif

    // e1 and e2 are the same size, shape, and location so gjk should return true
    auto e1 = entity::cube;
    //auto e2 = entity::cube;
    Entity e2 = Entity(std::vector<Vector3>{Vector3{-2, -2, -2},
                                            Vector3{-1, -1, 1},
                                            Vector3{-1, 1, -1},
                                            Vector3{-1, 1, 1},
                                            Vector3{1, -1, -1},
                                            Vector3{1, -1, 1},
                                            Vector3{1, 1, -1},
                                            Vector3{2, 2, 2}});
    bool hit = gjk::Run(e2, e1);
    if (hit) // this should be true
        std::cout << "Test Passed" << std::endl;
    else
        std::cout << "Test Failed" << std::endl;

    e2 = Entity(std::vector<Vector3>{Vector3{0, -1, -1},
                                     Vector3{0, -1, 1},
                                     Vector3{0, 1, -1},
                                     Vector3{0, 1, 1},
                                     Vector3{2, -1, -1},
                                     Vector3{2, -1, 1},
                                     Vector3{2, 1, -1},
                                     Vector3{2, 1, 1}});

    hit = gjk::Run(e2, e1);
    if (hit) // this should be true
        std::cout << "Test Passed" << std::endl;
    else
        std::cout << "Test Failed" << std::endl;

    return 0;
}