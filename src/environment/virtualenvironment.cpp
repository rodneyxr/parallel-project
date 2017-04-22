#include "virtualenvironment.hpp"

void VirtualEnvironment::AddEntity(Entity entity) {
    this->mutex.lock();
    this->entities.push_back(entity);
    this->mutex.unlock();
}

const std::vector<Entity> *VirtualEnvironment::GetEntities() const {
    return (const std::vector<Entity> *) &entities;
}
