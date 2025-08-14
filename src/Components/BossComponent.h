#pragma once
#include "../Component.h"

enum class BossVariant { Brute, Ranger, Mage };

struct BossComponent : public Component {
    BossVariant variant;
    explicit BossComponent(BossVariant v) : variant(v) {}
};
