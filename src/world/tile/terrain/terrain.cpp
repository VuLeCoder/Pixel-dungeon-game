#include "terrain.h"

void Terrain::setTerrainType(TerrainType type) {
    this->type = type;
}

TerrainType Terrain::getType() const {
    return type;
}

bool Terrain::isPassable() const {
    return terrainTable[static_cast<int>(type)].passable;
}

bool Terrain::isBlockVision() const {
    return terrainTable[static_cast<int>(type)].blockVision;
}

bool Terrain::isDanger() const {
    return terrainTable[static_cast<int>(type)].danger;
}

void Terrain::onEnter(Entity* entity, World& world) {
    if(!entity) return;

    switch(type) {
        case TerrainType::CHASM:
            // entity->fall();
            break;

        case TerrainType::GRASS:
            setTerrainType(TerrainType::FLOOR);
            break;

        case TerrainType::STAIR_DOWN:
            // if(entity->isPlayer()) {
            //     world.goToNextLevel();
            // }
            break;

        case TerrainType::STAIR_UP:
            // if(entity->isPlayer()) {
            //     world.goToPreviousLevel();
            // }
            break;

        case TerrainType::WATER:
            // entity->extinguish();
            break;

        default:
            break;
    }
}
