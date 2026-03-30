#pragma once
#include "trap.h"
#include "../../../utils/position.h"

#include "../../entity/entity.h"
#include "../../world.h"

class TeleportTrap : public Trap {
public:
    TrapType getTrapType() {
        return TrapType::TRAP_TELEPORT;
    }

    void trigger(Entity* entity, World* world) override {
        if(!entity) return;

        // Vector2 pos = world->getRandomFreeTile();
        // entity->setPos(pos.x, pos.y);

        afterTrigger();
    }
};