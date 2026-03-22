#pragma once
#include "trap.h"
#include "../../../utils/position.h"

class ExplosionTrap : public Trap {
    int damage = 20;

public:
    TrapType getTrapType() {
        return TrapType::TRAP_EXPLODE;
    }

    void trigger(Entity* entity, World& world) override {
        if(!entity) return;

        // Position pos = entity->getPosition();

        // for (int dx = -1; dx <= 1; dx++) {
        //     for (int dy = -1; dy <= 1; dy++) {

        //         int nx = pos.x + dx;
        //         int ny = pos.y + dy;

        //         Entity* e = world.getEntityAt({nx, ny});
        //         if (e) {
        //             e->takeDamage(damage);
        //         }
        //     }
        // }

        afterTrigger();
    }
};
