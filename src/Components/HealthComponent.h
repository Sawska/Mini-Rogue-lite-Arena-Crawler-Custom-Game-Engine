#pragma once
#include "../Component.h"

struct HealthComponent : public Component {
    int maxHealth;
    int currentHealth;

    HealthComponent(int maxHP) : maxHealth(maxHP), currentHealth(maxHP) {}
};
