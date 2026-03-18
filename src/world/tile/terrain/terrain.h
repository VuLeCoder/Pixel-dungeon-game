#pragma once

#include "terrain_type.h"
#include "../../entity/entity.h"
#include "../../world.h"

class Terrain {
private:
    TerrainType type;

public:
    void setTerrainType(TerrainType type) {
        this->type = type;
    }

    bool isPassable() const {
        return terrainTable[static_cast<int>(type)].passable;
    }
    
    bool isBlockVision() const {
        return terrainTable[static_cast<int>(type)].blockVision;
    }

    bool isDanger() const {
        return terrainTable[static_cast<int>(type)].danger;
    }
    
    void onEnter(Entity* entity, World& world);
};
