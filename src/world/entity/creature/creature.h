#pragma once

#include "../entity.h"
#include "../../../engine/effect/animation.h"

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
    ACTING
};

class Creature : public Entity {
private:
    static constexpr float SPEED = 16.0f / 0.3f;

protected:
    std::array<Animation, NUM_TYPE> anims;
    Animation* currAnim = nullptr;

    int hp;
    ActionState state = ActionState::IDLE;
    Direction dir;
    Vector2 targetPos;

public:
    Creature(float x, float y, World* world, Direction dir, int hp)
        : Entity(x, y, world), dir(dir), hp(hp) {}
        
    void update(float dt) override;
    void render() override;

    bool tryMove(int dx, int dy);

    virtual void attack(Entity* target) = 0;
    void takeDamage(int damage) override;

    bool isBlocking() const override { return true; }
    Vector2 getTargetPos() { return targetPos; }
    
    void setTargetPos(float nx, float ny) { targetPos = {nx, ny}; }
    void setState(ActionState state) { this->state = state; }
    void setAnimation(AnimType type);
    
    virtual void takeTurn() = 0;
};
