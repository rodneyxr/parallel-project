#include <iostream>
#include <random>
#include <functional>
#include <ctime>
#include "tools/entitygenerator.hpp"
#include "tools/stopwatch.h"
#include "aabb/aabb.h"
#include "gjk/gjk.hpp"

#define NUMBER_OF_ENTITIES 5000
#define VE_SIZE 1000


/*****************************************************************************
 * Global Variables
 *****************************************************************************/

/* virtual_environment will hold all the entities */
VirtualEnvironment virtual_environment;


/*****************************************************************************
 * Benchmarks
 *****************************************************************************/

void gjk_n2_sequential() {
    std::vector<Entity> entities = *virtual_environment.GetEntities();
    unsigned long size = entities.size();

    for (unsigned long j = 0; j < size; j++) {
        Entity e1 = entities[j];
        for (unsigned long k = j + 1; k < size; k++) {
            if (j == k) continue;
            Entity e2 = entities[k];
            gjk::Run(e1, e2);
        }
    }
}

void gjk_n2_openmp() {
    std::vector<Entity> entities = *virtual_environment.GetEntities();
    unsigned long size = entities.size();

    for (unsigned long j = 0; j < size; j++) {
        Entity e1 = entities[j];

        #pragma omp parallel for
        for (unsigned long k = j + 1; k < size; k++) {
            if (j == k) continue;
            Entity e2 = entities[k];
            gjk::Run(e1, e2);
        }
    }
}

void aabb_n2_sequential() {
    std::vector<Entity> entities = *virtual_environment.GetEntities();
    unsigned long size = entities.size();

    for (unsigned long j = 0; j < size; j++) {
        Entity e1 = entities[j];
        for (unsigned long k = j + 1; k < size; k++) {
            if (j == k) continue;
            Entity e2 = entities[k];
            aabb::Run(e1, e2);
        }
    }
}

void aabb_n2_openmp() {
    std::vector<Entity> entities = *virtual_environment.GetEntities();
    unsigned long size = entities.size();

    for (unsigned long j = 0; j < size; j++) {
        Entity e1 = entities[j];

        # pragma omp parallel for
        for (unsigned long k = j + 1; k < size; k++) {
            if (j == k) continue;
            Entity e2 = entities[k];
            aabb::Run(e1, e2);
        }
    }
}


/*****************************************************************************
 * Helper Functions
 *****************************************************************************/

/**
 * Runs a benchmark.
 *
 * @param benchmark_name the name of the benchmark to run.
 * @param benchmark_func the benchmark function.
 */
void benchmark(std::string benchmark_name, void (*benchmark_func)()) {
    // spaces before header
    std::cout << std::endl;
    std::cout << std::endl;

    // print header
    std::cout << "================ [ Benchmark " << benchmark_name << " ] ================" << std::endl;

    // initialize
    stop_watch watch;

    // benchmark
    watch.start();
    benchmark_func();
    watch.stop();

    // show results
    std::cout << watch << std::endl;
}

int main() {
    /* Helper class for generating varying shapes, positions and sizes */
    EntityGenerator gen(VE_SIZE, 0);

    // Create the virtual environment
    std::cout << "Creating virtual environment..." << std::endl;
    #pragma omp parallel for
    for (int i = 0; i < NUMBER_OF_ENTITIES; i++) {
        Entity cube = gen.GenerateCube();
        virtual_environment.AddEntity(cube);
    }

    // Run the benchmarks
    benchmark("gjk_n2_sequential", gjk_n2_sequential);
    benchmark("gjk_n2_openmp", gjk_n2_openmp);
    benchmark("aabb_n2_sequential", aabb_n2_sequential);
    benchmark("aabb_n2_openmp", aabb_n2_openmp);

    std::cout << std::endl;
    std::cout << std::endl;
    return 0;
}