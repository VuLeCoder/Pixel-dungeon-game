#include "terrain.h"

void Terrain::onEnter(Entity* entity, World& world) {
    if(!entity) return;

    switch(type) {
        case TerrainType::CHASM:
            entity->fall();
            break;

        case TerrainType::GRASS:
            setTerrainType(TerrainType::FLOOR);
            break;

        case TerrainType::STAIRS_DOWN:
            if(entity->isPlayer()) {
                world.goToNextLevel();
            }
            break;

        case TerrainType::STAIRS_UP:
            if(entity->isPlayer()) {
                world.goToPreviousLevel();
            }
            break;

        case TerrainType::WATER:
            entity->extinguish();
            break;

        default:
            break;
    }
}