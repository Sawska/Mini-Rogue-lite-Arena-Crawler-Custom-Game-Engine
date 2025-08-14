#pragma once
#include "../Component.h"
#include <vector>
#include <utility>

struct InventoryComponent : public Component {
    // (type, value)
    std::vector<std::pair<int,int>> items;
};
