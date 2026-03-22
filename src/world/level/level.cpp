#include "level.h"
#include "tile_rule.h"

#include <string>
#include <iostream>

std::string generateFileName(int depth) {
    return "level" + std::to_string(depth);
}

void Level::generateMap(int depth) {
    std::string fileName = generateFileName(depth);
    std::string terrainFile = fileName + "_Terrain";
    std::string doorFile = fileName + "_Door";
    std::string trapFile = fileName + "_Trap";
   
    std::vector<std::vector<int>> tileMatrix = AssetManager::GetMap(terrainFile);
    std::vector<std::vector<int>> doorMatrix = AssetManager::GetMap(doorFile);
    std::vector<std::vector<int>> trapMatrix = AssetManager::GetMap(trapFile);

   
    tiles.resize(MAP_SIZE, std::vector<Tile>(MAP_SIZE));
    for(int x=0; x<MAP_SIZE; ++x) {
        for(int y=0; y<MAP_SIZE; ++y) {

            if(trapMatrix[x][y] != NONE) {
                bool isHidden = (trapMatrix[x][y] == TRAP_HIDDEN);
                tiles[x][y].setTrapTile(tileMatrix[x][y], isHidden);
                continue;
            }

            if(doorMatrix[x][y] != NONE) {
                bool isHidden = (doorMatrix[x][y] == DOOR_HIDDEN);
                bool isLocked = (doorMatrix[x][y] == DOOR_LOCKED);
                tiles[x][y].setDoorTile(isLocked, isHidden);
                continue;
            }

            tiles[x][y].setTerrainType(tileMatrix[x][y]);
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
