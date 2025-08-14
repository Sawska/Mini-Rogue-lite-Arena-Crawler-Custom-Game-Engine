#pragma once
#include "../Entity.h"
#include "../Components/EnemyAIComponent.h"
#include "../Components/CombatComponent.h"
#include "../Components/PositionComponent.h"
#include <cmath>

class AISystem {
public:
    void update(Entity& entity, float targetX, float targetY) {
        auto pos = entity.getComponent<PositionComponent>();
        auto ai  = entity.getComponent<EnemyAIComponent>();
        if (!pos || !ai) return;

        auto cmb = entity.getComponent<CombatComponent>();
        float dx = targetX - pos->x;
        float dy = targetY - pos->y;
        float dist2 = dx*dx + dy*dy;

        // simple behavior:
        // if ranged and too close, back off; else, move toward player
        if (cmb && cmb->range > 1.5f && dist2 < 4.0f) {
            // kite away
            float len = std::sqrt(dist2); if (len == 0) len = 1;
            pos->x -= (dx/len) * ai->speed;
            pos->y -= (dy/len) * ai->speed;
        } else {
            if (targetX > pos->x) pos->x += ai->speed; else if (targetX < pos->x) pos->x -= ai->speed;
            if (targetY > pos->y) pos->y += ai->speed; else if (targetY < pos->y) pos->y -= ai->speed;
        }
    }
};
