#include "Game.h"
#include "Components/PositionComponent.h"
#include "Components/HealthComponent.h"
#include "Components/CombatComponent.h"
#include "Components/InventoryComponent.h"
#include "Components/ExperienceComponent.h"
#include "Components/SkillComponent.h"
#include "Components/BossComponent.h"
#include "Components/NameComponent.h"
#include "Systems/SaveSystem.h"
#include <iostream>
#include <cmath>

Game::Game()
: lootSystem(12345),
  dungeon(1234, 40, 20),
  levelManager(1234) {}

void Game::run() {
    // Create player
    player = &Player::create(manager);

    // Try to load save, otherwise build fresh level 0
    SaveMeta meta{0, levelManager.getSeed()};
    SaveSystem::load("save.json", *player, meta);
    levelIndex = meta.levelIndex;
    levelManager.buildLevel(levelIndex, manager, dungeon, *player);

    // demo loop
    for (int t=0; t<120; ++t) tick(t);

    // save on exit
    SaveSystem::save("save.json", *player, SaveMeta{levelIndex, levelManager.getSeed()});
}

void Game::tick(int t) {
    simulateInput(t);
    stepAIAndCombat();
    projectileSystem.update(manager);
    handleDeathsAndLoot();
    pickupSystem.tryPickup(*player, manager);

    // reach stairs? -> next level
    auto ppos = player->getComponent<PositionComponent>();
    if (dungeon.isStairs((int)ppos->x, (int)ppos->y)) nextLevel();

    printState(t);
}

void Game::simulateInput(int t) {
    // Simple scripted movement towards stairs center
    auto pos = player->getComponent<PositionComponent>();
    auto spd = player->getComponent<EnemyAIComponent>(); // speed holder
    if (!pos || !spd) return;

    // find boss or stairs to pursue
    float tx=-1, ty=-1;
    bool bossFound=false;
    for (auto& up : manager.getEntities()) {
        auto b = up->getComponent<BossComponent>();
        auto p = up->getComponent<PositionComponent>();
        auto h = up->getComponent<HealthComponent>();
        if (b && p && h && h->currentHealth > 0) {
            tx = p->x; ty = p->y; bossFound = true; break;
        }
    }
    if (!bossFound && !dungeon.roomCenters.empty()) {
        tx = (float)dungeon.roomCenters.back().first;
        ty = (float)dungeon.roomCenters.back().second;
    }

    if (tx>=0) {
        if (tx > pos->x) pos->x += spd->speed; else if (tx < pos->x) pos->x -= spd->speed;
        if (ty > pos->y) pos->y += spd->speed; else if (ty < pos->y) pos->y -= spd->speed;
    }
}

void Game::stepAIAndCombat() {
    auto ppos = player->getComponent<PositionComponent>();
    for (auto& up : manager.getEntities()) {
        Entity& e = *up;
        if (&e == player) continue;

        auto hp = e.getComponent<HealthComponent>();
        if (!hp || hp->currentHealth <= 0) continue;

        // AI moves toward player
        aiSystem.update(e, ppos->x, ppos->y);

        // enemy attempts to attack player
        combatSystem.tryAttack(e, *player, manager);
    }

    // player attacks nearest enemy if in range
    Entity* closest = nullptr;
    float best = 1e9f;
    auto aPos = player->getComponent<PositionComponent>();
    for (auto& up : manager.getEntities()) {
        Entity& e = *up;
        if (&e == player) continue;
        auto hp = e.getComponent<HealthComponent>();
        auto p  = e.getComponent<PositionComponent>();
        if (!hp || hp->currentHealth <= 0 || !p) continue;
        float dx = p->x - aPos->x;
        float dy = p->y - aPos->y;
        float d2 = dx*dx + dy*dy;
        if (d2 < best) { best = d2; closest = &e; }
    }
    if (closest) combatSystem.tryAttack(*player, *closest, manager);
}

void Game::handleDeathsAndLoot() {
    // drop loot and grant XP if enemies die
    for (auto& up : manager.getEntities()) {
        Entity& e = *up;
        if (&e == player) continue;
        auto hp = e.getComponent<HealthComponent>();
        if (!hp) continue;

        static bool granted[10000] = {false}; // crude guard for sample
        if (hp->currentHealth <= 0 && !granted[e.getId()]) {
            lootSystem.dropIfDead(e, manager);
            granted[e.getId()] = true;
            // give XP to player
            skillSystem.onGainXP(*player, 5);
        }
    }

    // auto-use items to showcase logic (no UI)
    auto inv = player->getComponent<InventoryComponent>();
    auto hp  = player->getComponent<HealthComponent>();
    auto skl = player->getComponent<SkillComponent>();
    auto cmb = player->getComponent<CombatComponent>();
    if (!inv || !hp || !skl || !cmb) return;

    for (auto& it : inv->items) {
        auto type = (ItemType)it.first;
        int val = it.second;
        if (val <= 0) continue;

        switch (type) {
            case ItemType::HealthPotion:
                hp->currentHealth = std::min(hp->maxHealth, hp->currentHealth + val);
                it.second = 0; break;
            case ItemType::DamageBoost:
                cmb->baseDamage += val;
                it.second = 0; break;
            case ItemType::SkillPoint:
                skl->skillPoints += val;
                // auto-assign: prioritize Strength
                skl->addPoint(SkillId::Strength);
                skillSystem.updateBonuses(*player);
                it.second = 0; break;
        }
    }
}

void Game::printState(int t) {
    if (t % 10 != 0) return;
    auto ppos = player->getComponent<PositionComponent>();
    auto php  = player->getComponent<HealthComponent>();
    auto xp   = player->getComponent<ExperienceComponent>();
    auto skl  = player->getComponent<SkillComponent>();

    std::cout << "Tick " << t
              << "  L" << levelIndex
              << "  Player(" << (int)ppos->x << "," << (int)ppos->y << ")"
              << "  HP " << php->currentHealth << "/" << php->maxHealth
              << "  LVL " << xp->level << " XP " << xp->xp << "/" << xp->next
              << "  STR " << skl->strengthLv << " AGI " << skl->agilityLv << " SOR " << skl->sorceryLv
              << "  SP "  << skl->skillPoints
              << "\n";
}

void Game::nextLevel() {
    ++levelIndex;
    levelManager.buildLevel(levelIndex, manager, dungeon, *player);
}
