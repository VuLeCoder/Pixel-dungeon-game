#pragma once
#include "raylib.h"
#include "AI_state.h"

#include <vector>

class Creature;
class Monster;
class PathFinder;

struct AIResult {
    Creature* target = nullptr;
    Vector2 pos = {-1, -1};
};

class MonsterAI {
private:
    Monster* monster;
    AIState state = AIState::SLEEP;

    Vector2 lastSeenPlayerPos = {-1, -1};

    PathFinder* pathFinder;

    static std::vector<Vector2> directions;
    
    AIState getAIState() const;
    void setAIState(AIState state);

    AIResult decideNextState();
    void moveRandom();
    void moveAlongPathTo(const AIResult& res);
    void moveAwayFrom(const AIResult& res);

public:
    MonsterAI(Monster* m);

    ~MonsterAI();
    void takeTurn();
};
