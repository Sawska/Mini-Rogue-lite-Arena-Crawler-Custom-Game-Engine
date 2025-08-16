#pragma once
#include "../EntityManager.h"
#include "../Components/PositionComponent.h"
#include "../Components/VelocityComponent.h"

class PhysicsSystem {
public:
    void update(EntityManager& manager) {
        for (auto& e : manager.getEntities()) {
            auto pos = e->getComponent<PositionComponent>();
            auto vel = e->getComponent<VelocityComponent>();
            if (pos && vel) {
                pos->x += vel->dx;
                pos->y += vel->dy;
            }
        }
    }
};
