#pragma once

#include <vector>
#include <unordered_map>
#include "../../utils/position.h"

#include "../tile/tile.h"
#include "../entity/creature/monster.h"
#include "../entity/item/item.h"

class Level {
private:
    static const int MAP_SIZE = 33;

    std::vector<std::vector<Tile>> tiles;

    std::vector<Monster*> enemies;
    std::vector<Item*> items;

public:
    void generateMap(int depth);
    void update();
    void render();

    bool isInside(int x, int y) const;

    bool isBlockVision(int x, int y) const;
    bool isPassable(int x, int y) const;
    bool isDanger(int x, int y) const;

    void addEntity(Entity* e);
    void removeEntity(Entity* e);
    Entity* getEntityAt(Position pos);

    void wakeUpAllMonsters();
    void spawnMonsterNear(Position pos);

    Position getRandomFreeTile();

    void onStep(Entity* e, Position pos);
};