//
// Created by rodney on 4/23/17.
//

#ifndef PARALLEL_AABB_H
#define PARALLEL_AABB_H


#include "../environment/entity.hpp"

class aabb {

public:

    /**
     * Check if e1's max is greater than e2's min and e1's min is less than e2's max
     *
     * @return true if there is a collision between e1 and e2; false otherwise.
     */
    static bool Run(const Entity &e1, const Entity &e2);

private:

    /**
     * @return the point in the entity that is closest to Vector3(-inf, -inf, -inf)
     */
    static Vector3 FindMinimumPoint(const Entity &e);

    /**
     * @return the point in the entity that is closest to Vector3(inf, inf, inf)
     */
    static Vector3 FindMaximumPoint(const Entity &e);

};


#endif //PARALLEL_AABB_H
