#ifndef PARALLEL_VIRTUALENVIRONMENT_HPP
#define PARALLEL_VIRTUALENVIRONMENT_HPP

#include <vector>
#include <mutex>
#include "entity.hpp"

/**
 * VirtualEnvironment represents a virtual world in 3D space. It many contain
 * zero to many entities.
 */
class VirtualEnvironment {
    std::vector<Entity> entities;

    /* mutex is to keep operations on entities thread safe */
    std::mutex mutex;

public:
    VirtualEnvironment() {};

    void AddEntity(Entity entity);

    std::vector<Entity> *GetEntities();
};


#endif //PARALLEL_VIRTUALENVIRONMENT_HPP
