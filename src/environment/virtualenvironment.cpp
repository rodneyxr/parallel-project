#include "virtualenvironment.hpp"

void VirtualEnvironment::AddEntity(Entity entity) {
    this->entities.push_back(entity);
}

const std::vector<Entity> *VirtualEnvironment::GetEntities() const {
    return (const std::vector<Entity> *) &entities;
}
