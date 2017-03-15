#include "entity.hpp"

Entity::Entity(std::vector<Vector3> points) {
    this->points = points;
}

const std::vector<Vector3> *Entity::GetPoints() const {
    return (const std::vector<Vector3>*) &this->points;
}