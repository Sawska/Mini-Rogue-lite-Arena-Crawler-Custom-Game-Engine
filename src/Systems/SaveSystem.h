#pragma once
#include "../EntityManager.h"
#include "../Entity.h"
#include "../Components/PositionComponent.h"
#include "../Components/HealthComponent.h"
#include "../Components/InventoryComponent.h"
#include "../Components/ExperienceComponent.h"
#include "../Components/SkillComponent.h"
#include <nlohmann/json.hpp>
#include <fstream>
#include <string>

using nlohmann::json;

struct SaveMeta {
    int levelIndex{0};
    uint32_t dungeonSeed{1234};
};

class SaveSystem {
public:
    static void save(const std::string& path, Entity& player, const SaveMeta& meta) {
        json j;
        j["meta"] = { {"levelIndex", meta.levelIndex}, {"dungeonSeed", meta.dungeonSeed} };

        auto pos = player.getComponent<PositionComponent>();
        auto hp  = player.getComponent<HealthComponent>();
        auto inv = player.getComponent<InventoryComponent>();
        auto xp  = player.getComponent<ExperienceComponent>();
        auto sk  = player.getComponent<SkillComponent>();

        if (pos) j["player"]["pos"] = { {"x", pos->x}, {"y", pos->y} };
        if (hp)  j["player"]["hp"]  = { {"cur", hp->currentHealth}, {"max", hp->maxHealth} };
        if (xp)  j["player"]["xp"]  = { {"level", xp->level}, {"xp", xp->xp}, {"next", xp->next} };
        if (sk)  j["player"]["skills"] = { 
            {"points", sk->skillPoints}, {"str", sk->strengthLv}, {"agi", sk->agilityLv}, {"sor", sk->sorceryLv}
        };
        if (inv) {
            j["player"]["inv"] = json::array();
            for (auto& p : inv->items) j["player"]["inv"].push_back({ {"type", p.first}, {"val", p.second} });
        }

        std::ofstream f(path);
        f << j.dump(2);
    }

    static void load(const std::string& path, Entity& player, SaveMeta& meta) {
        std::ifstream f(path);
        if (!f) return;
        json j; f >> j;

        meta.levelIndex  = j["meta"].value("levelIndex", 0);
        meta.dungeonSeed = j["meta"].value("dungeonSeed", 1234u);

        auto pos = player.getComponent<PositionComponent>();
        auto hp  = player.getComponent<HealthComponent>();
        auto inv = player.getComponent<InventoryComponent>();
        auto xp  = player.getComponent<ExperienceComponent>();
        auto sk  = player.getComponent<SkillComponent>();

        if (pos && j["player"].contains("pos")) {
            pos->x = j["player"]["pos"].value("x", 0.0f);
            pos->y = j["player"]["pos"].value("y", 0.0f);
        }
        if (hp && j["player"].contains("hp")) {
            hp->currentHealth = j["player"]["hp"].value("cur", 100);
            hp->maxHealth     = j["player"]["hp"].value("max", 100);
        }
        if (xp && j["player"].contains("xp")) {
            xp->level = j["player"]["xp"].value("level", 1);
            xp->xp    = j["player"]["xp"].value("xp", 0);
            xp->next  = j["player"]["xp"].value("next", 10);
        }
        if (sk && j["player"].contains("skills")) {
            sk->skillPoints = j["player"]["skills"].value("points", 0);
            sk->strengthLv  = j["player"]["skills"].value("str", 0);
            sk->agilityLv   = j["player"]["skills"].value("agi", 0);
            sk->sorceryLv   = j["player"]["skills"].value("sor", 0);
        }
        if (inv && j["player"].contains("inv")) {
            inv->items.clear();
            for (auto& it : j["player"]["inv"]) {
                inv->items.emplace_back(it.value("type", 0), it.value("val", 0));
            }
        }
    }
};
