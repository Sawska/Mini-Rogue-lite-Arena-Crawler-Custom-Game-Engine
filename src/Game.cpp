#include "Game.h"
#include <iostream>

void Game::run() {
    Entity& player = Player::create(manager);
    Entity& enemy = Enemy::spawn(manager, 5, 5);

    for (int tick = 0; tick < 10; ++tick) {
        std::cout << "Tick: " << tick << "\n";
        auto pos = player.getComponent<PositionComponent>();
        aiSystem.update(enemy, pos->x, pos->y);

        auto enemyPos = enemy.getComponent<PositionComponent>();
        std::cout << "Enemy pos: (" << enemyPos->x << ", " << enemyPos->y << ")\n";

        if (tick == 5) {
            std::cout << "Enemy attacks player!\n";
            healthSystem.damage(player, 20);
        }
    }
}
