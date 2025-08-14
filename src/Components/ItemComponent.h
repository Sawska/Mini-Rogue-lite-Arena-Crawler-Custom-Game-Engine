#pragma once
#include "../Component.h"
#include <string>

enum class ItemType { HealthPotion, DamageBoost, SkillPoint };

struct ItemComponent : public Component {
    ItemType type;
    int value;
    explicit ItemComponent(ItemType t, int v=0) : type(t), value(v) {}
};
