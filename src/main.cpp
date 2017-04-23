#include <iostream>
#include <random>
#include <functional>
#include <ctime>
#include "tools/entitygenerator.hpp"
#include "tools/stopwatch.h"
#include "gjk/gjk.hpp"

struct info_t {
    unsigned int checks;
    unsigned int collisions;
};

#define NUMBER_OF_ENTITIES 1000
#define VE_SIZE 1000


/*****************************************************************************
 * Global Variables
 *****************************************************************************/

/* virtual_environment will hold all the entities */
VirtualEnvironment virtual_environment;


/*****************************************************************************
 * Benchmarks
 *****************************************************************************/

void n2_sequential(info_t &info) {
    unsigned long size = virtual_environment.GetEntities()->size();
    for (unsigned long j = 0; j < size; j++) {
        Entity e1 = virtual_environment.GetEntities()->at(j);
        for (unsigned long k = j + 1; k < size; k++) {
            if (j == k) continue;
            Entity e2 = virtual_environment.GetEntities()->at(k);
            bool hit = gjk::Run(e2, e1);
            if (hit) {
                info.collisions++;
            }
            info.checks++;
        }
    }
}

void n2_openmp(info_t &info) {
    unsigned long size = virtual_environment.GetEntities()->size();
    for (unsigned long j = 0; j < size; j++) {
        Entity e1 = virtual_environment.GetEntities()->at(j);
        #pragma omp parallel for
        for (unsigned long k = j + 1; k < size; k++) {
            if (j == k) continue;
            Entity e2 = virtual_environment.GetEntities()->at(k);
            bool hit = gjk::Run(e2, e1);
            if (hit) {
                info.collisions++;
            }
            info.checks++;
        }
    }
}


/*****************************************************************************
 * Helper Functions
 *****************************************************************************/
void reset_benchmark(info_t &info, stop_watch &watch) {
    info.checks = 0;
    info.collisions = 0;
    watch.reset();
}

void print_results(const info_t &info, const stop_watch &watch) {
    std::cout << "Total Collisions: " << info.collisions << std::endl;
    std::cout << "Test Checks: " << info.checks << std::endl;
    std::cout << watch << std::endl;
}

int main() {
    /* Helper class for generating varying shapes, positions and sizes */
    EntityGenerator gen(VE_SIZE, 0);

    std::cout << "Creating virtual environment..." << std::endl;
#pragma omp parallel for
    for (int i = 0; i < NUMBER_OF_ENTITIES; i++) {
        Entity cube = gen.GenerateCube();
        virtual_environment.AddEntity(cube);
    }

    /* holds the results of each benchmark */
    info_t info;
    stop_watch watch;

    std::cout << std::endl;
    std::cout << std::endl;

    /* n2_sequential */
    reset_benchmark(info, watch);
    std::cout << "Running n2_sequential..." << std::endl;
    watch.start();
    n2_sequential(info);
    watch.stop();
    print_results(info, watch);

    std::cout << std::endl;
    std::cout << std::endl;

    /* n2_openmp */
    reset_benchmark(info, watch);
    std::cout << "Running n2_openmp..." << std::endl;
    watch.start();
    n2_openmp(info);
    watch.stop();
    print_results(info, watch);

    return 0;
}