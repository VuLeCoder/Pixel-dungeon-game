#pragma once
#include "../../entity/entity.h"
#include "../../world.h"

class Entity;
class World;

class Trap {
protected:
    bool revealed = false;
    bool armed = true;

    void afterTrigger() {
        reveal();
        disable();
    }

public:
    virtual ~Trap() {}

    virtual void trigger(Entity* entity, World& world) = 0;

    bool isArmed() const { return armed; }
    bool isRevealed() const { return revealed; }

    void reveal() { revealed = true; }
    void disable() { armed = false; }
};