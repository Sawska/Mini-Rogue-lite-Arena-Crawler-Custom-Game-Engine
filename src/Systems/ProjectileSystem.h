#pragma once
#include "../Entity.h"
#include "../EntityManager.h"
#include "../Components/ProjectileComponent.h"
#include "../Components/PositionComponent.h"
#include "../Components/HealthComponent.h"
#include <cmath>

class ProjectileSystem {
public:
    void update(EntityManager& mgr) {
        for (auto& up : mgr.getEntities()) {
            Entity& e = *up;
            auto proj = e.getComponent<ProjectileComponent>();
            if (!proj) continue;

            auto pos = e.getComponent<PositionComponent>();
            if (!pos) continue;

            // Move
            pos->x += proj->dx * proj->speed;
            pos->y += proj->dy * proj->speed;

            // Lifetime
            if (--proj->lifetime <= 0) {
                // simple: set damage to 0 and lifetime 0 means inert; no removal support
                proj->damage = 0;
                continue;
            }

            // Collision (very naive: hit first other entity within 0.75)
            for (auto& up2 : mgr.getEntities()) {
                Entity& t = *up2;
                if (t.getId() == proj->ownerId) continue;
                if (!t.getComponent<HealthComponent>()) continue;

                auto tp = t.getComponent<PositionComponent>();
                if (!tp) continue;

                float dx = pos->x - tp->x;
                float dy = pos->y - tp->y;
                if ((dx*dx + dy*dy) <= 0.75f*0.75f) {
                    auto th = t.getComponent<HealthComponent>();
                    th->currentHealth -= proj->damage;
                    proj->lifetime = 0; // consumed
                    proj->damage = 0;
                    break;
                }
            }
        }
    }
};
