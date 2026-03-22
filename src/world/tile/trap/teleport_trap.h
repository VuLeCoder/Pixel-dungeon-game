#pragma once
#include "trap.h"
#include "../../../utils/position.h"

class TeleportTrap : public Trap {
public:
    TrapType getTrapType() {
        return TrapType::TRAP_TELEPORT;
    }

    void trigger(Entity* entity, World& world) override {
        if(!entity) return;

        // Position pos = world.getRandomFreeTile();
        // entity->setPosition(pos);

        afterTrigger();
    }
};