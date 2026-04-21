#include "monster_ai.h"
#include "./../../world.h"
#include "./../../entity/creature/monster.h"
#include "./path_finder.h"

#include <cmath>
#include <iostream>

//helper
int distance(const Vector2& pos1, const Vector2& pos2) {
    float dx = (pos1.x - pos2.x) / TILE_SIZE;
    float dy = (pos1.y - pos2.y) / TILE_SIZE;
    return static_cast<int>(std::sqrt(dx * dx + dy * dy));
}

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

void MonsterAI::setAIState(AIState state) {
    this->state = state;
}

AIResult MonsterAI::decideNextState() {
    AIResult res;
    if(getAIState() == AIState::SLEEP) {
        int num = GetRandomValue(1, 3);
        if(num == 3) {
            setAIState(AIState::WANDER);
        }
        return res;
    }

    std::cout << lastSeenPlayerPos.x << std::endl;
    Vector2 playerPos = monster->canSeePlayer();
    if(playerPos.x < 0) {
        if(lastSeenPlayerPos.x < 0) {
            setAIState(AIState::WANDER);
            return res;
        }

        res.pos = lastSeenPlayerPos;
        switch(getAIState()) {
            case AIState::ATTACK:
            case AIState::WANDER:
                break;

            case AIState::CHASE:
                if(distance(monster->getPosition(), lastSeenPlayerPos) == 0) {
                    setAIState(AIState::WANDER);
                }
                return res;

            case AIState::FLEE:
                if(distance(monster->getPosition(), lastSeenPlayerPos) >= 10) {
                    setAIState(AIState::WANDER);
                }
                return res;
            
            default:
                break;
        }
        return res;
    }

    lastSeenPlayerPos = playerPos;
    res.pos = lastSeenPlayerPos;
    res.target = monster->getWorld()->getPlayer();

    setAIState(
        (monster->getCurrHP() <= 2) ? AIState::FLEE : AIState::CHASE
    );

    if(distance(monster->getPosition(), lastSeenPlayerPos) <= 1) {
        setAIState(AIState::ATTACK);
    }

    return res;
}

void MonsterAI::moveRandom() {
    int index = GetRandomValue(0, 7);
    monster->tryMove((int)directions[index].x, (int)directions[index].y);
}

void MonsterAI::moveAlongPathTo(const AIResult& res) {
    Vector2 targetPos = res.pos;
    pathFinder->findPath(
        monster->getPosition(),
        targetPos,
        monster->getWorld()
    );
}

void MonsterAI::moveAwayFrom(const AIResult& res) {
    Vector2 threatPos = res.pos;
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
    std::cout << "Suy nghi ";
    AIResult res = decideNextState();
    std::cout << "Toi nghi xong r " << std::endl;

    switch(state) {
        case AIState::SLEEP: break;

        case AIState::WANDER:
            moveRandom();
            break;

        case AIState::CHASE:
            moveAlongPathTo(res);
            std::cout << "Met vcl " << std::endl;
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
