#pragma once
#include "Entity.h"
#include "Components/HealthComponent.h"
#include "Components/PositionComponent.h"
#include "Components/EnemyAIComponent.h"
#include "EntityManager.h"

class Enemy {
public:
    static Entity& spawn(EntityManager& manager, float x, float y) {
        Entity& enemy = manager.createEntity();
        enemy.addComponent<HealthComponent>(50);
        enemy.addComponent<PositionComponent>(x, y);
        enemy.addComponent<EnemyAIComponent>(0.5f);
        return enemy;
    }
};
