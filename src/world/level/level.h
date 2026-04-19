#pragma once

#include <vector>
#include <unordered_map>

#include "../tile/tile.h"
#include "../entity/creature/monster.h"
#include "../entity/item/item.h"

class World;

struct MapData {
    std::vector<std::vector<int>> terrain;
    std::vector<std::vector<int>> door;
    std::vector<std::vector<int>> trap;
};

class Level {
private:
    static constexpr int MAP_SIZE = 33;
    World* world;

    std::vector<std::vector<Tile>> tiles;
    std::vector<Monster*> enemies;
    std::vector<Item*> items;

    MapData loadMapData(int depth);
    Tile buildTile(int x, int y, const MapData& data);

public:
    Level(World* world);

    World* getWorld();

    void generateMap(int depth);
    void update();
    void render();

    bool isInside(int x, int y) const;

    bool isBlockVision(int x, int y) const;
    bool isPassable(int x, int y) const;
    bool isDanger(int x, int y) const;

    void onStep(Entity* e, int x, int y);
    void onLeft(int x, int y);

    // void addEntity(Entity* e);
    // void removeEntity(Entity* e);
    // Entity* getEntityAt(Vector2 pos);

    // void wakeUpAllMonsters();
    // void spawnMonsterNear(Vector2 pos);
    Vector2 getRandomFreeTile();
};