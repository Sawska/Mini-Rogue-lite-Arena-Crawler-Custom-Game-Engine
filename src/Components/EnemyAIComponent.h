#pragma once
#include "../Component.h"

struct EnemyAIComponent : public Component {
    float speed;
    EnemyAIComponent(float s) : speed(s) {}
};
