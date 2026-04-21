#include "path_finder.h"
#include "./../../world.h"
#include "./../../Level/level.h"

#include <iostream>
#include <queue>

//private:
const int MAX_ATTEMPT = 10;

bool PathFinder::isPassable(int x, int y, Level* level) const {
    Entity* e = level->getEntityAtTile(x, y);
    if(e && e->isBlocking()) {
        return true;
    }

    return !level->isDanger(x, y) && level->isPassable(x, y);
}

//public:
std::vector<Vector2> PathFinder::directions = {
    { 0,  0 }, 
    { 0, -1 }, // UP
    { 1, -1 }, // UP-RIGHT
    { 1,  0 }, // RIGHT
    { 1,  1 }, // DOWN-RIGHT
    { 0,  1 }, // DOWN
    {-1,  1 }, // DOWN-LEFT
    {-1,  0 }, // LEFT
    {-1, -1 }  // UP-LEFT
};

int PathFinder::randomPath(int x, int y, Level* level) const {
    int attempt = 0;
    while(attempt++ < MAX_ATTEMPT) {
        int index = GetRandomValue(0, directions.size() - 1);
        if(isPassable(x + directions[index].x, y + directions[index].y, level)) {
            return index;
        }
    }
    return 0;
}

std::vector<int> PathFinder::findPath (
    Vector2 start, Vector2 goal, World* world
) {
    std::cout << "Dang duoi" << std::endl;
    std::vector<int> bestPath;

    // std::priority_queue



    return bestPath;
}

std::vector<int> PathFinder::runAway (
    Vector2 start, Vector2 threat, World* world
) {
    return {};
}
