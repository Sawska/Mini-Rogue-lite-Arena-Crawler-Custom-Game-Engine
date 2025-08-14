#pragma once
#include "../Component.h"


struct CombatComponent : public Component {
    int baseDamage{5};
    float range{1.0f};
    int cooldownTicks{10};
    int cooldown{0};

    explicit CombatComponent(int dmg=5, float r=1.0f, int cd=10)
        : baseDamage(dmg), range(r), cooldownTicks(cd) {}
};
