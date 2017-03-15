#ifndef PARALLEL_VIRTUALENVIRONMENT_HPP
#define PARALLEL_VIRTUALENVIRONMENT_HPP

#include <vector>
#include "entity.hpp"

/**
 * VirtualEnvironment represents a virtual world in 3D space. It many contain
 * zero to many entities.
 */
class VirtualEnvironment {
    std::vector<Entity> entities;

public:
    VirtualEnvironment() {};

    void AddEntity(Entity entity);

    const std::vector<Entity> *GetEntities() const;
};


#endif //PARALLEL_VIRTUALENVIRONMENT_HPP
