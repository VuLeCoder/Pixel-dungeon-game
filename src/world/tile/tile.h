#pragma once
#include "raylib.h"
#include <string>

#include "tile_index.h"
#include "terrain/terrain.h"
#include "door/door.h"

#include "trap/alarm_trap.h"
#include "trap/explode_trap.h"
#include "trap/spawn_trap.h"
#include "trap/spike_trap.h"
#include "trap/teleport_trap.h"

class Tile {
private:
    static const std::string TILE_NAME;
    static const int TILE_SIZE = 16;

    Terrain terrain;
    Trap* trap = nullptr;
    Door* door = nullptr;

    bool discovered = false;
    Vector2 tilePos;
    
    Vector2 tileImagePosition(int tileId);
    TerrainType determineTileType(int tileId);
    Trap* createTrap(int tileId);

public:
    void setTerrainType(int tileId);
    void setDoorTile(bool isLocked, bool isHidden);
    void setTrapTile(int trapId, bool isHidden);
    void discoverTile();

    bool isDiscovered() const;
    bool isPassable() const;
    bool isBlockVision() const;
    bool isDanger() const;

    void onEnter(Entity* entity, World* world);
    void onLeft();

    void update();
    void render(int x, int y);
};
