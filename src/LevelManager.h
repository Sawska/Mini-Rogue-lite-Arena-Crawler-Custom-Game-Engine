#pragma once
#include "EntityManager.h"
#include "Dungeon.h"
#include "Enemy.h"
#include "Components/CombatComponent.h"
#include "Components/BossComponent.h"
#include "Components/NameComponent.h"
#include <random>

class LevelManager {
public:
    explicit LevelManager(uint32_t seed=1234) : seed(seed), rng(seed) {}

    void buildLevel(int index, EntityManager& mgr, Dungeon& dungeon, Entity& player) {
        dungeon = Dungeon(seed + index, 40, 20);
        dungeon.generate(6 + index/2);

        // place player at first room
        auto [px,py] = dungeon.roomCenters.front();
        if (auto ppos = player.getComponent<PositionComponent>()) { ppos->x = px; ppos->y = py; }

        // spawn enemies in each room except first & last (boss in last)
        for (size_t i=1; i+1<dungeon.roomCenters.size(); ++i) {
            auto [ex,ey] = dungeon.roomCenters[i];
            spawnEnemyPack(mgr, ex, ey, 2 + (int)i);
        }
        // boss on last room
        auto [bx,by] = dungeon.roomCenters.back();
        spawnBoss(mgr, bx, by, index);
    }

    uint32_t getSeed() const { return seed; }

private:
    uint32_t seed;
    std::mt19937 rng;

    void spawnEnemyPack(EntityManager& mgr, float x, float y, int n) {
        for (int i=0;i<n;i++) {
            Entity& e = Enemy::spawn(mgr, x + i%2, y + i/2);
            e.addComponent<NameComponent>("Goblin");
            e.addComponent<CombatComponent>(3, 1.0f, 12);
        }
    }

    void spawnBoss(EntityManager& mgr, float x, float y, int levelIndex) {
        Entity& b = Enemy::spawn(mgr, x, y);
        b.addComponent<NameComponent>("Boss");
        BossVariant v = (BossVariant)(levelIndex % 3);
        b.addComponent<BossComponent>(v);
        switch (v) {
            case BossVariant::Brute:   b.getComponent<HealthComponent>()->maxHealth = b.getComponent<HealthComponent>()->currentHealth = 200; b.addComponent<CombatComponent>(10,1.0f,8); break;
            case BossVariant::Ranger:  b.getComponent<HealthComponent>()->maxHealth = b.getComponent<HealthComponent>()->currentHealth = 140; b.addComponent<CombatComponent>(6,4.0f,6); break;
            case BossVariant::Mage:    b.getComponent<HealthComponent>()->maxHealth = b.getComponent<HealthComponent>()->currentHealth = 120; b.addComponent<CombatComponent>(5,5.0f,5); break;
        }
    }
};
