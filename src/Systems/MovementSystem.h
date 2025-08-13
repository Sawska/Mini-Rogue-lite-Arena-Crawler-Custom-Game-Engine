#pragma once
#include "../Entity.h"
#include "../Components/PositionComponent.h"
#include <iostream>

class MovementSystem {
public:
    void move(Entity& entity, char direction) {
        auto pos = entity.getComponent<PositionComponent>();
        if (!pos) return;

        switch (direction) {
            case 'w': pos->y -= 1; break;
            case 's': pos->y += 1; break;
            case 'a': pos->x -= 1; break;
            case 'd': pos->x += 1; break;
            default: break;
        }
    }
};
