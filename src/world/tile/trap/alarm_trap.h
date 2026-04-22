#pragma once
#include "trap.h"

class AlarmTrap : public Trap {
private:
    static constexpr int alarmRange = 15;

public:
    TrapType getTrapType() override {
        return TrapType::TRAP_ALARM;
    }

    void trigger(Entity* entity, World* world) override;
};