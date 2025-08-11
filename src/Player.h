#pragma once
#include "Entity.h"
#include "Components/HealthComponent.h"
#include "Components/PositionComponent.h"
#include "EntityManager.h"

class Player {
public:
    static Entity& create(EntityManager& manager) {
        Entity& player = manager.createEntity();
        player.addComponent<HealthComponent>(100);
        player.addComponent<PositionComponent>(0, 0);
        return player;
    }
};
