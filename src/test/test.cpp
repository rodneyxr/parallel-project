#include <iostream>
#include <random>
#include <functional>
#include <ctime>
#include "../tools/entitygenerator.hpp"
#include "../tools/stopwatch.h"
#include "../gjk/gjk.hpp"

bool test1() {
    auto e1 = entity::cube;
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

    return hit;
}

bool test2() {
    auto e1 = entity::cube;
    auto e2 = Entity(std::vector<Vector3>{Vector3{0, -1, -1},
                                     Vector3{0, -1, 1},
                                     Vector3{0, 1, -1},
                                     Vector3{0, 1, 1},
                                     Vector3{2, -1, -1},
                                     Vector3{2, -1, 1},
                                     Vector3{2, 1, -1},
                                     Vector3{2, 1, 1}});

    bool hit = gjk::Run(e2, e1);
    if (hit) // this should be true
        std::cout << "Test Passed" << std::endl;
    else
        std::cout << "Test Failed" << std::endl;
}

void header(std::string s) {
    std::cout << "**********[ " << s << " ]**********" << std::endl;
}

int main() {
    header("Test 1");
    test1();

    header("Test 2");
    test2();
    return 0;
}