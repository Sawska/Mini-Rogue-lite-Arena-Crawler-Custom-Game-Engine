#pragma once
#include "EntityManager.h"
#include "Player.h"
#include "Enemy.h"
#include "Dungeon.h"
#include "LevelManager.h"

#include "Systems/HealthSystem.h"
#include "Systems/AISystem.h"
#include "Systems/MovementSystem.h"
#include "Systems/CombatSystem.h"
#include "Systems/ProjectileSystem.h"
#include "Systems/PickupSystem.h"
#include "Systems/LootSystem.h"
#include "Systems/SkillSystem.h"
#include "Systems/SaveSystem.h"

#include <vector>
#include <string>

class Game {
public:
    Game();
    void run();

private:
    EntityManager manager;
    HealthSystem healthSystem;
    AISystem aiSystem;
    MovementSystem movementSystem;
    CombatSystem combatSystem;
    ProjectileSystem projectileSystem;
    PickupSystem pickupSystem;
    LootSystem lootSystem;
    SkillSystem skillSystem;

    Dungeon dungeon;
    LevelManager levelManager;

    Entity* player{nullptr};
    int levelIndex{0};

    void tick(int t);
    void simulateInput(int t); // placeholder movement/attacks without UI
    void stepAIAndCombat();
    void handleDeathsAndLoot();
    void printState(int t);
    void nextLevel();
};
