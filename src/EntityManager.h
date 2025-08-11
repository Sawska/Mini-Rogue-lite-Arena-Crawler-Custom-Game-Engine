#pragma once
#include "Entity.h"
#include <vector>
#include <memory>

class EntityManager {
public:
    Entity& createEntity() {
        entities.push_back(std::make_unique<Entity>(nextId++));
        return *entities.back();
    }

    std::vector<std::unique_ptr<Entity>>& getEntities() {
        return entities;
    }

private:
    int nextId = 0;
    std::vector<std::unique_ptr<Entity>> entities;
};
