#pragma once
#include "../Entity.h"
#include "../Components/HealthComponent.h"
#include <iostream>

class HealthSystem {
public:
    void damage(Entity& entity, int amount) {
        auto health = entity.getComponent<HealthComponent>();
        if (health) {
            health->currentHealth -= amount;
            if (health->currentHealth <= 0) {
                health->currentHealth = 0;
                std::cout << "Entity " << entity.getId() << " has died.\n";
            }
        }
    }
};
