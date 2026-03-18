#include "trap.h"

class AlarmTrap : public Trap {
public:
    void trigger(Entity* entity, World& world) override {
        world.wakeUpAllMonsters();
        afterTrigger();
    }
};