#pragma once
#include "raylib.h"
#include <vector>

class World;
class Level;

class PathFinder {
private:
    bool isPassable(int x, int y, Level* level) const;

public:
    static std::vector<Vector2> directions;

    int randomPath(int x, int y, Level* level) const;

    std::vector<int> findPath (
        Vector2 start,
        Vector2 goal,
        World* world
    );

    std::vector<int> runAway (
        Vector2 start,
        Vector2 threat,
        World* world
    );
};
