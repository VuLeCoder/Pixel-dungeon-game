#include "monster_ai.h"
#include "./../../world.h"
#include "./../../entity/creature/monster.h"
#include "./path_finder.h"
#include "./../../../utils/helper.h"

#include <iostream>

//private:
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

    // if(distance(monster->getPosition(), lastSeenPlayerPos) <= 1) {
    //     setAIState(AIState::ATTACK);
    // }

    return res;
}

void MonsterAI::moveRandom() {
    std::cout << "Player o dau roi" << std::endl;
    
    int x = monster->getPosition().x / TILE_SIZE;
    int y = monster->getPosition().y / TILE_SIZE;
    int index = pathFinder->randomPath(x, y, monster->getWorld()->getCurrLevel());
    std::cout << "Toi di bua" << std::endl;

    x = PathFinder::directions[index].x;
    y = PathFinder::directions[index].y;
    monster->tryMove(x, y);
}

void MonsterAI::moveAlongPathTo(const AIResult& res) {
    Vector2 targetPos = res.pos;
    int index = pathFinder->findPath(
        monster->getPosition(),
        targetPos,
        monster->getWorld()
    );

    int x = PathFinder::directions[index].x;
    int y = PathFinder::directions[index].y;
    monster->tryMove(x, y);
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
            // monster->attack(res.target);
            break;
    }
}

MonsterAI::~MonsterAI() {
    delete pathFinder;
    pathFinder = nullptr;
}
