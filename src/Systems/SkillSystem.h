#pragma once
#include "../Entity.h"
#include "../Components/SkillComponent.h"
#include "../Components/ExperienceComponent.h"
#include "../Components/CombatComponent.h"
#include "../Components/EnemyAIComponent.h"
#include "../Components/HealthComponent.h"

class SkillSystem {
public:
    // convert level ups into skill points and apply passive effects
    void updateBonuses(Entity& e) {
        auto skl = e.getComponent<SkillComponent>();
        auto cmb = e.getComponent<CombatComponent>();
        auto ai  = e.getComponent<EnemyAIComponent>();
        auto hp  = e.getComponent<HealthComponent>();
        if (!skl) return;

        // Apply passive bonuses
        if (cmb) {
            cmb->baseDamage = 5 + (skl->strengthLv * 2) + (skl->sorceryLv); // sorcery lightly buffs all damage
        }
        if (ai) {
            ai->speed = 0.5f + 0.1f * skl->agilityLv; // player may have EnemyAI for movement reuse; ignore if not
        }
        if (hp) {
            hp->maxHealth = 100 + (skl->strengthLv * 10);
            if (hp->currentHealth > hp->maxHealth) hp->currentHealth = hp->maxHealth;
        }
    }

    void onGainXP(Entity& e, int amount) {
        auto xp = e.getComponent<ExperienceComponent>();
        auto skl = e.getComponent<SkillComponent>();
        if (!xp || !skl) return;

        bool leveled = xp->addXP(amount);
        if (leveled) {
            // +1 skill point per level
            ++skl->skillPoints;
            updateBonuses(e);
        }
    }
};
