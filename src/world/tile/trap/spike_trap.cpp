#include "trap.h"

class SpikeTrap : public Trap {
private:
    int damage = 10;

public:
    void trigger(Entity* entity, World& world) override {
        if (!entity) return;
        entity->takeDamage(damage);
        afterTrigger();
    }
};