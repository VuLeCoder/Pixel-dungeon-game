#pragma once
#include "raylib.h"
#include "AI_state.h"

#include <vector>

class Creature;
class Monster;
class PathFinder;

struct AIResult {
    Creature* target;
};

class MonsterAI {
private:
    Monster* monster;
    AIState state = AIState::IDLE;

    PathFinder* pathFinder;

    static std::vector<Vector2> directions;
    
    AIState getAIState() const;

    AIResult decideNextState();
    void moveRandom();
    void moveAlongPathTo(const AIResult& res);
    void moveAwayFrom(const AIResult& res);

public:
    MonsterAI(Monster* m);

    ~MonsterAI();
    void takeTurn();
};
