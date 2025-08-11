#pragma once
#include "../Entity.h"
#include "../Components/PositionComponent.h"
#include "../Components/EnemyAIComponent.h"

class AISystem {
public:
    void update(Entity& entity, float playerX, float playerY) {
        auto pos = entity.getComponent<PositionComponent>();
        auto ai = entity.getComponent<EnemyAIComponent>();
        if (pos && ai) {
            if (playerX > pos->x) pos->x += ai->speed;
            else if (playerX < pos->x) pos->x -= ai->speed;
            if (playerY > pos->y) pos->y += ai->speed;
            else if (playerY < pos->y) pos->y -= ai->speed;
        }
    }
};
