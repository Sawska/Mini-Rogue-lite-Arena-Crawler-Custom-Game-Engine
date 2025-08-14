#pragma once
#include "../EntityManager.h"
#include "../Components/HealthComponent.h"
#include "../Components/PositionComponent.h"
#include "../Components/ItemComponent.h"
#include "../Components/NameComponent.h"
#include <random>

class LootSystem {
public:
    explicit LootSystem(uint32_t seed=12345) : rng(seed) {}

    void dropIfDead(Entity& e, EntityManager& mgr) {
        auto h = e.getComponent<HealthComponent>();
        if (!h || h->currentHealth > 0) return;

        auto pos = e.getComponent<PositionComponent>();
        if (!pos) return;

        std::uniform_int_distribution<int> d(0, 99);
        int roll = d(rng);

        // 50% potion, 25% damage boost, 25% skill point
        if (roll < 50) spawnItem(mgr, pos->x, pos->y, ItemType::HealthPotion, 25, "Potion");
        else if (roll < 75) spawnItem(mgr, pos->x, pos->y, ItemType::DamageBoost, 2, "Damage+");
        else spawnItem(mgr, pos->x, pos->y, ItemType::SkillPoint, 1, "SkillPoint");

        // prevent duplicate drops
        h->currentHealth = -9999;
    }

private:
    std::mt19937 rng;

    void spawnItem(EntityManager& mgr, float x, float y, ItemType t, int v, const char* name) {
        Entity& it = mgr.createEntity();
        it.addComponent<ItemComponent>(t, v);
        it.addComponent<PositionComponent>(x, y);
        it.addComponent<NameComponent>(name);
    }
};
