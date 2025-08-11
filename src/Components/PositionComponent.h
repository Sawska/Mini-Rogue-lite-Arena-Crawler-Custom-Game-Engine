#pragma once
#include "../Component.h"

struct PositionComponent : public Component {
    float x, y;
    PositionComponent(float x = 0, float y = 0) : x(x), y(y) {}
};
