#include "entity.hpp"

Entity::Entity(std::vector<Vector3> points) {
    this->points = points;
}

const std::vector<Vector3> *Entity::GetPoints() const {
    return (const std::vector<Vector3> *) &this->points;
}

Vector3 Entity::GetCentroid() const {
    Vector3 centroid = vec3::zero;
    for (auto p : points) {
        centroid.x += p.x;
        centroid.y += p.y;
        centroid.z += p.z;
    }
    return centroid / Vector3(points.size());
}
