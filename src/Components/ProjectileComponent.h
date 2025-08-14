#pragma once
#include "../Component.h"

struct ProjectileComponent : public Component {
    float dx{0}, dy{0};
    float speed{1.0f};
    int damage{1};
    int lifetime{20};
    int ownerId{-1};
    ProjectileComponent(float dx_, float dy_, float spd, int dmg, int life, int owner)
        : dx(dx_), dy(dy_), speed(spd), damage(dmg), lifetime(life), ownerId(owner) {}
};
