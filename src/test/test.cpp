#include <iostream>
#include <random>
#include <functional>
#include <ctime>
#include "../tools/entitygenerator.hpp"
#include "../gjk/gjk.hpp"
#include "../aabb/aabb.h"

/*****************************************************************************
 * Test Cases
 *****************************************************************************/

bool test_gjk_hit() {
    auto e1 = entity::cube;
    Entity e2 = Entity(std::vector<Vector3>{
            Vector3{-2, -2, -2},
            Vector3{-1, -1, 1},
            Vector3{-1, 1, -1},
            Vector3{-1, 1, 1},
            Vector3{1, -1, -1},
            Vector3{1, -1, 1},
            Vector3{1, 1, -1},
            Vector3{2, 2, 2}
    });
    return gjk::Run(e1, e2);
}

bool test_aabb_hit() {
    auto e1 = entity::cube;
    Entity e2 = Entity(std::vector<Vector3>{
            Vector3{-2, -2, -2},
            Vector3{-1, -1, 1},
            Vector3{-1, 1, -1},
            Vector3{-1, 1, 1},
            Vector3{1, -1, -1},
            Vector3{1, -1, 1},
            Vector3{1, 1, -1},
            Vector3{2, 2, 2}
    });
    return aabb::Run(e1, e2);
}

/*****************************************************************************
 * Helper Functions
 *****************************************************************************/
void header(std::string s) {
    std::cout << std::endl;
    std::cout << std::endl;
    std::cout << "********** [ " << s << " ] **********" << std::endl;
}

/**
 * Runs a test case.
 *
 * @param test_name the name of the test case.
 * @param test_func the test function. Must return a bool indicating a pass or fail.
 */
void test(std::string test_name, bool (*test_func)()) {
    header(test_name);
    if (test_func())
        std::cout << "----------- SUCCESS -----------" << std::endl;
    else
        std::cout << "xxxxxxxxx TEST FAILED xxxxxxxxx" << std::endl;

}


/*****************************************************************************
 * Test Driver
 *****************************************************************************/
int main() {
    test("test_gjk_hit", test_gjk_hit);
    test("test_aabb_hit", test_aabb_hit);
    return 0;
}