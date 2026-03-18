#include "trap.h"

class TeleportTrap : public Trap {
public:
    void trigger(Entity* entity, World& world) override {
        if(!entity) return;

        Tile* t = world.getRandomFreeTile();
        entity->setPosition(t);

        afterTrigger();
    }
};