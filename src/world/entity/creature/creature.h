#pragma once

#include "../entity.h"
#include "../../../engine/effect/animation.h"
#include "stats.h"

#include <array>

constexpr int TILE_SIZE = 16;

enum Direction {
    LEFT,
    RIGHT
};

enum AnimType {
    IDLE,
    WALK,
    ATK,
    USE,
    USE_SCROLL,
    DEATH
};
constexpr int NUM_TYPE = 6;

enum class ActionState {
    IDLE,
    MOVING,
    ATTACKING,
    USE,
    USE_SCROLL,
    DEATH
};

class Creature : public Entity {
private:
    static constexpr float SPEED = 16.0f / 0.3f;
    Stats stats;
    int currHP;
    bool processTurn = false;

    void startTurn() { processTurn = true; }
    void endTurn() { processTurn = false; }

    void updateMovement(float dt);
    void updateAttack();
    void updateDeath();

protected:
    std::array<Animation, NUM_TYPE> anims;
    Animation* currAnim = nullptr;

    ActionState state = ActionState::IDLE;
    Direction dir;
    Vector2 targetPos;

    virtual void updateUse();
    virtual void updateUseScroll();

public:
    Creature(float x, float y, World* world, Direction dir, Stats stats)
        : Entity(x, y, world), dir(dir), stats(stats) {
            currHP = stats.maxHP;
            setTargetPos(getPosition().x, getPosition().y);
        }
        
    void update(float dt) override;
    void render() override;

    bool tryMove(int dx, int dy);
    void destroy() override;
    virtual void attack(Entity* target) = 0;
    void takeDamage(int damage) override;
    
    bool isBlocking() const override { return true; }
    Vector2 getTargetPos() const { return targetPos; }
    Stats getStats() const { return stats; }
    int getCurrHP() const { return currHP; }
    
    void setStats(Stats newStats) { stats = newStats; currHP = stats.maxHP; }
    void setTargetPos(float nx, float ny) { targetPos = {nx, ny}; }
    void setState(ActionState state);
    void setAnimation(AnimType type);
    
    virtual void takeTurn() = 0;
    bool hasStartedTurn() const { return processTurn == true; }
    bool isEndTurn() const { return processTurn == false; }
};
