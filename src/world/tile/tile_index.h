#pragma once

#include "terrain/terrain_type.h"
#include "trap/trap_type.h"
#include "door/door_state.h"

constexpr int ID_FLOOR          = 0;
constexpr int ID_GRASS          = 1;
constexpr int ID_CRUSHED_GRASS  = 2;
constexpr int ID_WATER_1        = 3;
constexpr int ID_WATER_16       = 18;
constexpr int ID_CHASM_1        = 19;
constexpr int ID_CHASM_2        = 20;
constexpr int ID_STAIR_UP       = 21;
constexpr int ID_STAIR_DOWN     = 22;
constexpr int ID_WALL           = 23;

constexpr int ID_DOOR_LOCKED   = 24;
constexpr int ID_DOOR_CLOSED   = 25;
constexpr int ID_DOOR_OPEN     = 26;

constexpr int ID_TRAP_DISABLE   = 29;
constexpr int ID_TRAP_SPIKE     = 30;
constexpr int ID_TRAP_EXPLODE   = 31;
constexpr int ID_TRAP_TELEPORT  = 32;
constexpr int ID_TRAP_ALARM     = 33;
constexpr int ID_TRAP_SPAWN     = 34;

extern const TerrainType tileTypeMap[24];

int trapTileId(TrapType t);
int doorTileId(DoorState t);