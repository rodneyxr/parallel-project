#ifndef PARALLEL_ENTITY_HPP
#define PARALLEL_ENTITY_HPP

#include <vector>
#include "../tools/vector3.hpp"

/**
 * An Entity represents an object in the virtual environment. It contains a
 * set of points to make a convex shape in 3D space.
 */
class Entity {
    std::vector<Vector3> points;

public:
    Entity(std::vector<Vector3> points);

    const std::vector<Vector3> *GetPoints() const;

    /**
     * NOTE: this will break if entity has no points.
     *
     * @return the centroid for this entity.
     */
    Vector3 GetCentroid() const;
};

namespace entity {
    static const Entity cube{std::vector<Vector3>{
            Vector3{-1, -1, -1},
            Vector3{-1, -1, 1},
            Vector3{-1, 1, -1},
            Vector3{-1, 1, 1},
            Vector3{1, -1, -1},
            Vector3{1, -1, 1},
            Vector3{1, 1, -1},
            Vector3{1, 1, 1}
    }};
}


#endif //PARALLEL_ENTITY_HPP
