#include "tile.h"

bool Tile::isPassable() const {
    if(door && !door->isPassable())
        return false;

    return terrain.isPassable();
}

bool Tile::isBlockVision() const {
    if(door && door->isBlockVision())
        return true;

    return terrain.isBlockVision();
}

bool Tile::isDanger() const {
    if(door) return false;
    if(trap) return true;
    return terrain.isDanger();
}

void Tile::onEnter(Entity* entity, World& world) {
    if(trap && trap->isArmed()) {
        trap->trigger(entity, world);
        return;
    }

    terrain.onEnter(entity, world);
}