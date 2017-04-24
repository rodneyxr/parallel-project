#include "virtualenvironment.hpp"

void VirtualEnvironment::AddEntity(Entity entity) {
    this->mutex.lock();
    this->entities.push_back(entity);
    this->mutex.unlock();
}

std::vector<Entity> *VirtualEnvironment::GetEntities() {
    return &entities;
}
