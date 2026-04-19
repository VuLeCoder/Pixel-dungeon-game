#include "level.h"
#include "tile_rule.h"
#include "../../engine/asset_manager.h"

#include <string>
#include <iostream>

//private:
MapData Level::loadMapData(int depth) {
    std::string base = "level" + std::to_string(depth);

    return {
        AssetManager::GetMap(base + '_' + std::string(AssetManager::TERRAIN)),
        AssetManager::GetMap(base + '_' + std::string(AssetManager::DOOR)),
        AssetManager::GetMap(base + '_' + std::string(AssetManager::TRAP))
    };
}

Tile Level::buildTile(int x, int y, const MapData& data) {
    Tile tile;
    int terrain = data.terrain[x][y];

    int trap = data.trap[x][y];
    if(trap != NONE) {
        tile.setTrapTile(terrain, trap == TRAP_HIDDEN);
        return tile;
    }

    int door = data.door[x][y];
    if(door != NONE) {
        tile.setDoorTile(
            door == DOOR_LOCKED,
            door == DOOR_HIDDEN
        );
        return tile;
    }

    tile.setTerrainType(terrain);
    return tile;
}

//public:
Level::Level(World* world) : world(world) {}

World* Level::getWorld() { return world; }


void Level::generateMap(int depth) {
    MapData data = loadMapData(depth);

    tiles = std::vector<std::vector<Tile>>(MAP_SIZE, std::vector<Tile>(MAP_SIZE));

    for(int x=0; x<MAP_SIZE; ++x) {
        for(int y=0; y<MAP_SIZE; ++y) {
            tiles[x][y] = buildTile(x, y, data);            
        }
    }
}

void Level::update() {
    for(int x=0; x<MAP_SIZE; ++x) {
        for(int y=0; y<MAP_SIZE; ++y) {
            tiles[x][y].update();
        }
    }
}

void Level::render() {
    for(int x=0; x<MAP_SIZE; ++x) {
        for(int y=0; y<MAP_SIZE; ++y) {
            tiles[x][y].render(y, x);
        }
    }
}


bool Level::isBlockVision(int x, int y) const {
    return tiles[x][y].isBlockVision();
}
#include <iostream>
bool Level::isPassable(int x, int y) const {
    if(x == 14 && y == 15) {
        std::cout << tiles[x][y].isPassable() <<std::endl;
    }
    return tiles[x][y].isPassable();
}

bool Level::isDanger(int x, int y) const {
    return tiles[x][y].isDanger();
}


void Level::onStep(Entity* e, int x, int y) {
    tiles[x][y].onEnter(e, getWorld());
}

void Level::onLeft(int x, int y) {
    tiles[x][y].onLeft();
}

Vector2 Level::getRandomFreeTile() {
    
}
