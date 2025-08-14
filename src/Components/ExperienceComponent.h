#pragma once
#include "../Component.h"

struct ExperienceComponent : public Component {
    int level{1};
    int xp{0};
    int next{10}; // next level threshold

    bool addXP(int amount) {
        xp += amount;
        bool leveled = false;
        while (xp >= next) {
            xp -= next;
            ++level;
            next = next + 10 + (level * 5);
            leveled = true;
        }
        return leveled;
    }
};
