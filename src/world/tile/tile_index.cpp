#include "tile_index.h"

const TerrainType tileTypeMap[24] = {
    TerrainType::FLOOR,          // 0
    TerrainType::GRASS,          // 1
    TerrainType::CRUSHED_GRASS,  // 2

    // 3 -> 18 (WATER)
    TerrainType::WATER, TerrainType::WATER, TerrainType::WATER,
    TerrainType::WATER, TerrainType::WATER, TerrainType::WATER,
    TerrainType::WATER, TerrainType::WATER, TerrainType::WATER,
    TerrainType::WATER, TerrainType::WATER, TerrainType::WATER,
    TerrainType::WATER, TerrainType::WATER, TerrainType::WATER,
    TerrainType::WATER,

    TerrainType::CHASM,          // 19
    TerrainType::CHASM,          // 20
    TerrainType::STAIR_UP,       // 21
    TerrainType::STAIR_DOWN,     // 22
    TerrainType::WALL            // 23
};

int trapTileId(TrapType t) {
    switch (t) {
        case TrapType::TRAP_ALARM:      return ID_TRAP_ALARM;
        case TrapType::TRAP_TELEPORT:   return ID_TRAP_TELEPORT;
        case TrapType::TRAP_EXPLODE:    return ID_TRAP_EXPLODE;
        case TrapType::TRAP_SPAWN:      return ID_TRAP_SPAWN;
        case TrapType::TRAP_SPIKE:      return ID_TRAP_SPIKE;
        default: return ID_FLOOR;
    }
}

int doorTileId(DoorState t) {
    switch (t) {
        case DoorState::LOCKED: return ID_DOOR_LOCKED;
        case DoorState::CLOSED: return ID_DOOR_CLOSED;
        case DoorState::OPEN:   return ID_DOOR_OPEN;
        default: return ID_WALL;
    }
}