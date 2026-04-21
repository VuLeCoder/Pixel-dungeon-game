#pragma once
#include "raylib.h"
#include <vector>

class World;

class PathFinder {
public:
    std::vector<Vector2> findPath (
        Vector2 start,
        Vector2 goal,
        World* world
    );

    std::vector<Vector2> runAway (
        Vector2 start,
        Vector2 threat,
        World* world
    );
};
