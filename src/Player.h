#pragma once
#include "Entity.h"
#include "Components/HealthComponent.h"
#include "Components/PositionComponent.h"
#include "Components/InventoryComponent.h"
#include "Components/SkillComponent.h"
#include "Components/ExperienceComponent.h"
#include "Components/CombatComponent.h"
#include "Components/EnemyAIComponent.h"
#include "Components/NameComponent.h"
#include "EntityManager.h"

class Player {
public:
    static Entity& create(EntityManager& manager) {
        Entity& p = manager.createEntity();
        p.addComponent<NameComponent>("Hero");
        p.addComponent<HealthComponent>(100);
        p.addComponent<PositionComponent>(0, 0);
        p.addComponent<InventoryComponent>();
        p.addComponent<SkillComponent>();
        p.addComponent<ExperienceComponent>();
        p.addComponent<CombatComponent>(6, 3.5f, 8); // has ranged
        p.addComponent<EnemyAIComponent>(0.8f);      // reuse speed holder for movement
        return p;
    }
};
