#include "trap.h"
#include "alarm_trap.h"

#include "./../../world.h"
#include "./../../entity/entity.h"

void AlarmTrap::trigger(Entity* entity, World* world) {
    world->wakeUpAllMonsters(entity->getPosition(), alarmRange);
    afterTrigger();
}

