#include "trap.h"

class SpawnTrap : public Trap {
public:
    void trigger(Entity* entity, World& world) override {
        if(!entity) return;
        world.spawnMonsterNear(entity->getPosition());
        afterTrigger();
    }
}