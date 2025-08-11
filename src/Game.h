#pragma once
#include "EntityManager.h"
#include "Player.h"
#include "Enemy.h"
#include "Systems/HealthSystem.h"
#include "Systems/AISystem.h"

class Game {
public:
    void run();
private:
    EntityManager manager;
    HealthSystem healthSystem;
    AISystem aiSystem;
};
