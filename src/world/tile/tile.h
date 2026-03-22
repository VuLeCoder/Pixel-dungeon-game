#pragma once
#include <string>
#include "../../engine/asset_manager.h"

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
    Position tilePos;
    
    Position tileImagePosition(int tileId) {
        if(tileId == -1) {
            return {0, 0};
        }

        int x = tileId % 8;
        int y = tileId / 8;
        return {x * TILE_SIZE, y * TILE_SIZE};
    }

    TerrainType determineTileType(int tileId) {
        if(tileId < 0 || tileId >= std::size(tileTypeMap)) {
            return TerrainType::CHASM;
        }
        return tileTypeMap[tileId];
    }

    Trap* createTrap(int tileId) {
        switch(tileId) {
            case ID_TRAP_ALARM:     return new AlarmTrap();
            case ID_TRAP_EXPLODE:   return new ExplosionTrap();
            case ID_TRAP_SPAWN:     return new SpawnTrap();
            case ID_TRAP_SPIKE:     return new SpikeTrap();
            case ID_TRAP_TELEPORT:  return new TeleportTrap();
            default: return nullptr;
        }
    }

public:
    void setTerrainType(int tileId) {
        tilePos = tileImagePosition(tileId);
        terrain.setTerrainType(determineTileType(tileId));
    }

    void setDoorTile(bool isLocked, bool isHidden) {
        door = new Door(isLocked, isHidden);
    }

    void setTrapTile(int trapId, bool isHidden) {
        trap = createTrap(trapId);
        if(!isHidden) {
            trap->reveal();
        }
    }

    bool isDiscovered() {
        return discovered;
    }

    void discoverTile() {
        discovered = true;
    }

    bool isPassable() const;
    bool isBlockVision() const;
    bool isDanger() const;

    void onEnter(Entity* entity, World& world);

    void update();
    void render(int x, int y);
};
