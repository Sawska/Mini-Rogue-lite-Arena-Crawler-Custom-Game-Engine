#pragma once
#include "EntityManager.h"
#include "Player.h"
#include "Enemy.h"
#include "Systems/HealthSystem.h"
#include "Systems/AISystem.h"
#include "Systems/MovementSystem.h"
#include "Systems/CombatSystem.h"
#include <vector>

class Game {
public:
    void run();
private:
    EntityManager manager;
    HealthSystem healthSystem;
    AISystem aiSystem;
    MovementSystem movementSystem;
    CombatSystem combatSystem;
    std::vector<Entity*> enemies;

    void spawnEnemy(float x, float y);
    void printState(Entity& player);
};
