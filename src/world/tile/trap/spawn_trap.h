#pragma once
#include "trap.h"

class SpawnTrap : public Trap {
public:
    TrapType getTrapType() override {
        return TrapType::TRAP_SPAWN;
    }

    void trigger(Entity* entity, World* world) override {
        if(!entity) return;
        // world.spawnMonsterNear(entity->getPosition());
        afterTrigger();
    }
};