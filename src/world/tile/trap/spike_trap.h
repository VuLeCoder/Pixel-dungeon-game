#pragma once
#include "trap.h"

class SpikeTrap : public Trap {
private:
    int damage = 10;

public:
    TrapType getTrapType() {
        return TrapType::TRAP_SPIKE;
    }

    void trigger(Entity* entity, World& world) override {
        if (!entity) return;
        // entity->takeDamage(damage);
        afterTrigger();
    }
};