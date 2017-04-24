#ifndef PARALLEL_GJK_H
#define PARALLEL_GJK_H

#include "../tools/vector3.hpp"
#include "../environment/entity.hpp"
#include "../environment/virtualenvironment.hpp"
#include "simplex.hpp"

class gjk {

public:
    static bool Run(Entity &e1, Entity &e2);

private:
    /**
     * Finds the max point along a direction.
     *
     * @param direction The direction to search for a max point.
     * @return the furthest point in the direction.
     */
    static Vector3 FindMaxPointInDirection(const Entity &entity, const Vector3 direction);

    static Vector3 Support(const Entity &e1, const Entity &e2, const Vector3 direction);

    static bool ContainsOrigin(Simplex &simplex, Vector3 &direction);

};


#endif //PARALLEL_GJK_H
