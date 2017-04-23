#include "entitygenerator.hpp"

#include <assert.h>
#include <iostream>

//EntityGenerator::EntityGenerator(unsigned int ve_size) {
//    EntityGenerator(ve_size, std::random_device()());
//}

EntityGenerator::EntityGenerator(int ve_size, std::random_device::result_type seed) {
    this->random_engine = std::default_random_engine(seed);
    SetVirtualEnvironmentSize(ve_size);
    SetEntitySizeRange(5, 15);
}

void EntityGenerator::SetVirtualEnvironmentSize(int ve_size) {
    this->pos_distribution = std::uniform_real_distribution<double>(-ve_size, ve_size);
}

void EntityGenerator::SetEntitySizeRange(int min_size, int max_size) {
    assert(min_size > 0);
    assert(min_size <= max_size);
    this->size_distribution = std::uniform_real_distribution<double>(min_size, max_size);
}

Entity EntityGenerator::GenerateCube() {
    Vector3 center = RandomVector();
    double size = size_distribution(random_engine) / 2;

    std::vector<Vector3> points;
    Vector3 size_vec = Vector3{size, size, size};

    auto corner = [size_vec, center](Vector3 v) { return v * size_vec + center; };
    for (const Vector3 point : *entity::cube.GetPoints())
        points.push_back(corner(point));

    return Entity{points};
}

Vector3 EntityGenerator::RandomVector() {
    return Vector3{pos_distribution(random_engine), pos_distribution(random_engine), pos_distribution(random_engine)};
}


