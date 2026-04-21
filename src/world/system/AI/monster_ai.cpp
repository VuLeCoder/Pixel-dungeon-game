#include "monster_ai.h"
#include "./../../entity/creature/monster.h"
#include "./path_finder.h"

//private:
std::vector<Vector2> MonsterAI::directions = {
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

AIState MonsterAI::getAIState() const {
    return state;
}

AIResult MonsterAI::decideNextState() {

}

void MonsterAI::moveRandom() {
    int index = GetRandomValue(0, 7);
    monster->tryMove((int)directions[index].x, (int)directions[index].y);
}

void MonsterAI::moveAlongPathTo(const AIResult& res) {
    Vector2 targetPos = res.target->getPosition();
    pathFinder->findPath(
        monster->getPosition(),
        targetPos,
        monster->getWorld()
    );
}

void MonsterAI::moveAwayFrom(const AIResult& res) {
    Vector2 threatPos = res.target->getPosition();
    pathFinder->runAway(
        monster->getPosition(),
        threatPos,
        monster->getWorld()
    );
}

//public:
MonsterAI::MonsterAI(Monster* m) : monster(m) {
    pathFinder = new PathFinder();
}

void MonsterAI::takeTurn() {
    AIResult res = decideNextState();

    switch(state) {
        case AIState::IDLE: break;

        case AIState::WANDER:
            moveRandom();
            break;

        case AIState::CHASE:
            moveAlongPathTo(res);
            break;

        case AIState::FLEE:
            moveAwayFrom(res);
            break;

        case AIState::ATTACK:
            monster->attack(res.target);
            break;
    }
}

MonsterAI::~MonsterAI() {
    delete pathFinder;
    pathFinder = nullptr;
}
