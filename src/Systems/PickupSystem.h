#pragma once
#include "../Entity.h"
#include "../EntityManager.h"
#include "../Components/PositionComponent.h"
#include "../Components/ItemComponent.h"
#include "../Components/InventoryComponent.h"
#include "../Components/NameComponent.h"

class PickupSystem {
public:
    void tryPickup(Entity& picker, EntityManager& mgr) {
        auto ppos = picker.getComponent<PositionComponent>();
        auto inv  = picker.getComponent<InventoryComponent>();
        if (!ppos || !inv) return;

        for (auto& up : mgr.getEntities()) {
            Entity& e = *up;
            if (&e == &picker) continue;
            auto item = e.getComponent<ItemComponent>();
            if (!item) continue;

            auto ipos = e.getComponent<PositionComponent>();
            if (!ipos) continue;

            if ((int)ppos->x == (int)ipos->x && (int)ppos->y == (int)ipos->y) {
                inv->items.emplace_back((int)item->type, item->value);
                // "remove" item: convert to inert marker
                e.addComponent<NameComponent>("[picked]");
                e.getComponent<ItemComponent>()->value = 0;
            }
        }
    }
};
