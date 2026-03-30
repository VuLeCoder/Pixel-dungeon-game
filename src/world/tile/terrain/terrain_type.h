#pragma once

enum class TerrainType {
    FLOOR,
    WALL,
    WATER,
    STAIR_DOWN,
    STAIR_UP,
    CHASM,
    GRASS,
    CRUSHED_GRASS
};

struct TerrainInfo {
    bool passable;
    bool blockVision;
    bool danger;
};

const TerrainInfo terrainTable[] = {
    {true, false, false},  // FLOOR
    {false, true, false},  // WALL
    {true, false, false},  // WATER
    {true, false, false},  // STAIRS_DOWN
    {true, false, false},  // STAIRS_UP
    {true, false, true},  // CHASM
    {true, true, false},   // GRASS
    {true, false, false},   // CRUSHED_GRASS
};
