#pragma once
#include "trap.h"

#include "../../entity/entity.h"
#include "../../entity/creature/player.h"
#include "../../entity/creature/monster.h"
#include "../../world.h"

class TeleportTrap : public Trap {
public:
    TrapType getTrapType() {
        return TrapType::TRAP_TELEPORT;
    }

    void trigger(Entity* entity, World* world) override {
        if(!entity) return;

        Vector2 pos = world->getRandomFreeTile();
        entity->setPos(pos.x, pos.y);
        if(entity->isBlocking()) {
            if (entity->isPlayer()) {
                Player* player = static_cast<Player*>(entity);
                player->setTargetPos(pos.x, 1+pos.y);
            } else {
                Monster* monster = static_cast<Monster*>(entity);
                monster->setTargetPos(pos.x, pos.y);
            }
        }

        afterTrigger();
    }
};