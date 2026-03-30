#pragma once
#include "trap.h"

class AlarmTrap : public Trap {
public:
    TrapType getTrapType() {
        return TrapType::TRAP_ALARM;
    }

    void trigger(Entity* entity, World* world) override {
        // world.wakeUpAllMonsters();
        afterTrigger();
    }
};