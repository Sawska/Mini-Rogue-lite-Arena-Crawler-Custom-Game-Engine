#pragma once
#include "../Entity.h"
#include "../Components/HealthComponent.h"
#include "../Components/PositionComponent.h"
#include <cmath>
#include <iostream>

class CombatSystem {
public:
    void attack(Entity& attacker, Entity& target, int damage) {
        auto attackerPos = attacker.getComponent<PositionComponent>();
        auto targetPos = target.getComponent<PositionComponent>();

        if (!attackerPos || !targetPos) return;

        float dist = std::sqrt(
            std::pow(attackerPos->x - targetPos->x, 2) +
            std::pow(attackerPos->y - targetPos->y, 2)
        );

        if (dist <= 1.0f) { 
            auto targetHealth = target.getComponent<HealthComponent>();
            if (targetHealth) {
                targetHealth->currentHealth -= damage;
                std::cout << "Entity " << target.getId() << " takes " 
                          << damage << " damage! HP: " 
                          << targetHealth->currentHealth << "/" 
                          << targetHealth->maxHealth << "\n";
                if (targetHealth->currentHealth <= 0) {
                    std::cout << "Entity " << target.getId() << " has died!\n";
                }
            }
        }
    }
};
