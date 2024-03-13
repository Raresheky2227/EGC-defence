#include "EntityCollection.h"

EntityCollection::EntityCollection() : entityCount(0) {
    // empty
}

void EntityCollection::addEntity(const Entity& entity) {
    entities.push_back(entity);
    entityCount++;
}

void EntityCollection::removeEntity(int index) {
    if (index >= 0 && index < entityCount) {
        entities.erase(entities.begin() + index);
        entityCount--;
    }
}

int EntityCollection::getEntityCount() const {
    return entityCount;
}

Entity& EntityCollection::getEntity(int index) {
    if (index >= 0 && index < entityCount) {
        return entities[index];
    }
    else {
        return entities[0];
    }
}
