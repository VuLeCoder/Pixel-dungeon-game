#pragma once

#include <vector>
#include <unordered_map>

#include "../tile/tile.h"
#include "../entity/item/item.h"

class World;
class Monster;

struct MapData {
    std::vector<std::vector<int>> terrain;
    std::vector<std::vector<int>> door;
    std::vector<std::vector<int>> trap;
};

class Level {
public:
    static constexpr int MAP_SIZE = 33;
    
private:
    World* world;
    Vector2 stairUpPos, stairDownPos;

    std::vector<std::vector<Tile>> tiles;
    std::vector<Monster*> enemies;
    std::vector<Item*> items;

    MapData loadMapData(int depth);
    Tile buildTile(int x, int y, const MapData& data);

public:
    Level(World* world);

    World* getWorld() { return world; }
    std::vector<Monster*>& getMonsters() { return enemies; }
    Vector2 getStairUpPos() { return stairUpPos; }
    Vector2 getStairDownPos() { return stairUpPos; }

    void generateMap(int depth);
    void update(float dt);
    void render();

    bool isBlockVision(int x, int y) const;
    bool isPassable(int x, int y) const;
    bool isDanger(int x, int y) const;
    void discover(int x, int y);

    void onStep(Entity* e, int x, int y);
    void onLeft(int x, int y);

    // void addEntity(Entity* e);
    // void removeEntity(Entity* e);
    Entity* getEntityAtTile(int x, int y);

    // void wakeUpAllMonsters();
    void spawnMonsterNear(Vector2 pos);
    Vector2 getRandomFreeTile();
};