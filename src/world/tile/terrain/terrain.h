#pragma once

#include "terrain_type.h"

class World;
class Entity;

class Terrain {
private:
    TerrainType type;

public:
    void setTerrainType(TerrainType type);
    TerrainType getType() const;

    bool isPassable() const;
    bool isBlockVision() const;
    bool isDanger() const;
    
    void onEnter(Entity* entity, World* world);
};
