#pragma once
#include "raylib.h"

class World;

class Entity {
protected:
    World* world;
    Vector2 pos;
    bool alive = true;

public:
    Entity(float x, float y, World* world) : pos({x, y}), world(world) {}
    virtual ~Entity() {}

    bool isAlive() const { return alive; }
    void destroy() { alive = false; }

    Vector2 getPosition() const { return pos; }
    void setPos(float nx, float ny) { pos = {nx, ny}; }
    World* getWorld() { return world; }

    virtual bool isBlocking() const = 0;
    virtual bool isPlayer() const = 0;
    
    virtual void takeDamage(int damage) = 0;
    virtual void fall() = 0;
    virtual void update(float dt) {}
    virtual void render() = 0;
};
