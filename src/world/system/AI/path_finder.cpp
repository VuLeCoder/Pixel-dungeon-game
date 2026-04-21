#include "path_finder.h"
#include "./../../world.h"
#include "./../../Level/level.h"
#include "./../../../utils/helper.h"

#include <iostream>

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

int PathFinder::findPath (
    Vector2 start, Vector2 goal, World* world
) {
    int cx = start.x / TILE_SIZE, cy = start.y / TILE_SIZE;
    int gx = goal.x / TILE_SIZE, gy = goal.y / TILE_SIZE;
    Vector2 tmp;

    std::cout << "Dang duoi" << std::endl;
    int bestMove = 0;
    int bestScore = distance(start, goal);

    for(int i=1; i<directions.size(); ++i) {
        if(!isPassable(
            cx + directions[i].x, 
            cy + directions[i].y, 
            world->getCurrLevel()
        )) continue;

        tmp = {
            static_cast<float>(cx + directions[i].x) * TILE_SIZE,
            static_cast<float>(cy + directions[i].y) * TILE_SIZE
        };
        int score = distance(tmp, goal);
        
        if(score < bestScore) {
            bestMove = i;
            bestScore = score;
        }
    }
    return bestMove;
}

int PathFinder::runAway (
    Vector2 start, Vector2 threat, World* world
) {
    int cx = start.x / TILE_SIZE, cy = start.y / TILE_SIZE;
    int gx = threat.x / TILE_SIZE, gy = threat.y / TILE_SIZE;
    Vector2 tmp;

    std::cout << "Dang chay" << std::endl;
    int bestMove = 0;
    int bestScore = distance(start, threat);

    for(int i=1; i<directions.size(); ++i) {
        if(!isPassable(
            cx + directions[i].x, 
            cy + directions[i].y, 
            world->getCurrLevel()
        )) continue;

        tmp = {
            static_cast<float>(cx + directions[i].x) * TILE_SIZE,
            static_cast<float>(cy + directions[i].y) * TILE_SIZE
        };
        int score = distance(tmp, threat);
        
        if(score > bestScore) {
            bestMove = i;
            bestScore = score;
        }
    }
    return bestMove;
}
