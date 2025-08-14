#pragma once
#include "../Component.h"

enum class SkillId { Strength, Agility, Sorcery };

struct SkillComponent : public Component {
    int skillPoints{0};
    int strengthLv{0}; // +damage
    int agilityLv{0};  // +speed
    int sorceryLv{0};  // +ranged damage

    void addPoint(SkillId id) {
        if (skillPoints <= 0) return;
        --skillPoints;
        switch (id) {
            case SkillId::Strength: ++strengthLv; break;
            case SkillId::Agility:  ++agilityLv;  break;
            case SkillId::Sorcery:  ++sorceryLv;  break;
        }
    }
};
