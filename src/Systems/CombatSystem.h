#pragma once
#include "../Entity.h"
#include "../Components/HealthComponent.h"
#include "../Components/PositionComponent.h"
#include "../Components/CombatComponent.h"
#include "../Components/ProjectileComponent.h"
#include "../Components/NameComponent.h"
#include "../EntityManager.h"
#include <cmath>

class CombatSystem {
public:
    void tryAttack(Entity& attacker, Entity& target, EntityManager& mgr) {
        auto aPos = attacker.getComponent<PositionComponent>();
        auto tPos = target.getComponent<PositionComponent>();
        auto aCmb = attacker.getComponent<CombatComponent>();
        if (!aPos || !tPos || !aCmb) return;

        if (aCmb->cooldown > 0) { --aCmb->cooldown; return; }

        float dx = tPos->x - aPos->x;
        float dy = tPos->y - aPos->y;
        float dist = std::sqrt(dx*dx + dy*dy);

        if (dist <= 1.0f) {
            // melee
            dealDamage(target, aCmb->baseDamage);
            aCmb->cooldown = aCmb->cooldownTicks;
        } else if (dist <= aCmb->range) {
            // ranged -> spawn projectile
            float len = (dist==0)?1.0f:dist;
            float ndx = dx/len, ndy = dy/len;

            Entity& proj = mgr.createEntity();
            proj.addComponent<PositionComponent>(aPos->x, aPos->y);
            proj.addComponent<ProjectileComponent>(ndx, ndy, 1.5f, aCmb->baseDamage, 15, attacker.getId());
            proj.addComponent<NameComponent>("Projectile");

            aCmb->cooldown = aCmb->cooldownTicks;
        }
    }

private:
    void dealDamage(Entity& target, int dmg) {
        auto th = target.getComponent<HealthComponent>();
        if (!th) return;
        th->currentHealth -= dmg;
        if (th->currentHealth <= 0) th->currentHealth = 0;
    }
};
