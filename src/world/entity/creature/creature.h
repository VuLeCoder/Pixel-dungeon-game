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
    SLEEP,
    IDLE,
    WALK,
    ATK,
    USE,
    USE_SCROLL,
    DEATH
};
constexpr int NUM_TYPE = 7;

enum State {
    IDLE_STATE,
    ACTION_STATE
};

class Creature : public Entity {
protected:
    std::array<Animation, NUM_TYPE> anims;
    Animation* currAnim = nullptr;

    int hp;
    State state = State::IDLE_STATE;
    Direction dir;
    Vector2 nextPos, targetPos;

public:
    Creature(float x, float y, World* world, Direction dir, int hp)
        : Entity(x, y, world), dir(dir), hp(hp) {}

    bool isBlocking() const override { return true; }
    void takeDamage(int damage) override;
    
    void setAnimation(AnimType type);

    void render() override;
};
