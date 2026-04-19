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

bool Level::isPassable(int x, int y) const {
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
    std::vector<Vector2> freeTiles;
    for (int y = 0; y < MAP_SIZE; ++y) {
        for (int x = 0; x < MAP_SIZE; ++x) {
            if (!isPassable(x, y)) continue;
            if (isDanger(x, y)) continue;
            // if (getEntityAt({(float)x, (float)y}) != nullptr) continue;

            freeTiles.push_back({(float)x, (float)y});
        }
    }

    if (freeTiles.empty()) {
        return {-1, -1};
    }

    int index = GetRandomValue(0, freeTiles.size() - 1);
    freeTiles[index].x *= TILE_SIZE;
    freeTiles[index].y *= TILE_SIZE;
    return {freeTiles[index].y, freeTiles[index].x};
}

Entity* Level::getEntityAt(Vector2 pos) {
    Vector2 tmpPos;
    for(Entity* e : enemies) {
        tmpPos = e->getPosition();
        if(tmpPos.x == pos.x && tmpPos.y == pos.y) {
            return e;
        }
    }

    for(Entity* i : items) {
        tmpPos = i->getPosition();
        if(tmpPos.x == pos.x && tmpPos.y == pos.y) {
            return i;
        }
    }

    return nullptr;
}
