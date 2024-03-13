#pragma once
#include "Entity.h"
#include <vector>

class EntityCollection {
public:
    EntityCollection();

    void addEntity(const Entity& entity);

    void removeEntity(int index);

    int getEntityCount() const;

    Entity& getEntity(int index);

private:
    std::vector<Entity> entities;
    int entityCount;
};