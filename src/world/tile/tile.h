#pragma once

#include "terrain/terrain.h"
#include "door/door.h"
#include "trap/trap.h"

struct Tile {
    Terrain terrain;
    bool discovered = false;

    Trap* trap = nullptr;
    Door* door = nullptr;

    bool isPassable() const;
    bool isBlockVision() const;
    bool isDanger() const;

    void onEnter(Entity* entity, World& world);
};
