#include <iostream>
#include <random>
#include <functional>
#include <ctime>
#include <thread>
#include "tools/entitygenerator.hpp"
#include "tools/stopwatch.h"
#include "aabb/aabb.h"
#include "gjk/gjk.hpp"

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

void gjk_n2_cppthread8() {
    unsigned long n = 8; // number of threads
    std::vector<Entity> entities = *virtual_environment.GetEntities();
    unsigned long size = entities.size();
    std::thread *t = new std::thread[n];
    unsigned long work_part = (unsigned long) floor((float) size / (float)n);

    // run n threads
    for (unsigned long i = 0; i < n; i++) {
        unsigned long start = i * work_part;
        unsigned long end = start + work_part;
        t[i] = std::thread([start, end, entities, size] {
            for (unsigned long j = start; j < end; j++) {
                Entity e1 = entities[j];
                for (unsigned long k = j + 1; k < size; k++) {
                    if (j == k) continue;
                    Entity e2 = entities[k];
                    gjk::Run(e1, e2);
                }
            }
        });
    }

    // join the threads
    for (unsigned long i = 0; i < n; i++) {
        t[i].join();
    }
}

void gjk_n2_cppthread16() {
    unsigned long n = 16; // number of threads
    std::vector<Entity> entities = *virtual_environment.GetEntities();
    unsigned long size = entities.size();
    std::thread *t = new std::thread[n];
    unsigned long work_part = (unsigned long) floor((float) size / (float)n);

    // run n threads
    for (unsigned long i = 0; i < n; i++) {
        unsigned long start = i * work_part;
        unsigned long end = start + work_part;
        t[i] = std::thread([start, end, entities, size] {
            for (unsigned long j = start; j < end; j++) {
                Entity e1 = entities[j];
                for (unsigned long k = j + 1; k < size; k++) {
                    if (j == k) continue;
                    Entity e2 = entities[k];
                    gjk::Run(e1, e2);
                }
            }
        });
    }

    // join the threads
    for (unsigned long i = 0; i < n; i++) {
        t[i].join();
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

void aabb_n2_cppthread8() {
    unsigned long n = 8; // number of threads
    std::vector<Entity> entities = *virtual_environment.GetEntities();
    unsigned long size = entities.size();
    std::thread *t = new std::thread[n];
    unsigned long work_part = (unsigned long) floor((float) size / (float)n);


    // run n threads
    for (unsigned long i = 0; i < n; i++) {
        unsigned long start = i * work_part;
        unsigned long end = start + work_part;
        t[i] = std::thread([start, end, entities, size] {
            for (unsigned long j = start; j < end; j++) {
                Entity e1 = entities[j];
                for (unsigned long k = j + 1; k < size; k++) {
                    if (j == k) continue;
                    Entity e2 = entities[k];
                    aabb::Run(e1, e2);
                }
            }
        });
    }

    // join the threads
    for (unsigned long i = 0; i < n; i++) {
        t[i].join();
    }
}

void aabb_n2_cppthread16() {
    unsigned long n = 16; // number of threads
    std::vector<Entity> entities = *virtual_environment.GetEntities();
    unsigned long size = entities.size();
    std::thread *t = new std::thread[n];
    unsigned long work_part = (unsigned long) floor((float) size / (float)n);

    // run n threads
    for (unsigned long i = 0; i < n; i++) {
        unsigned long start = i * work_part;
        unsigned long end = start + work_part;
        t[i] = std::thread([start, end, entities, size] {
            for (unsigned long j = start; j < end; j++) {
                Entity e1 = entities[j];
                for (unsigned long k = j + 1; k < size; k++) {
                    if (j == k) continue;
                    Entity e2 = entities[k];
                    aabb::Run(e1, e2);
                }
            }
        });
    }

    // join the threads
    for (unsigned long i = 0; i < n; i++) {
        t[i].join();
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
    benchmark("gjk_n2_cppthread 8 threads", gjk_n2_cppthread8);
    benchmark("gjk_n2_cppthread 16 threads", gjk_n2_cppthread16);

    benchmark("aabb_n2_sequential", aabb_n2_sequential);
    benchmark("aabb_n2_openmp", aabb_n2_openmp);
    benchmark("aabb_n2_cppthread 8 threads", aabb_n2_cppthread8);
    benchmark("aabb_n2_cppthread 16 threads", aabb_n2_cppthread16);

    std::cout << std::endl;
    std::cout << std::endl;
    return 0;
}