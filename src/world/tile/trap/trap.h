#pragma once
#include "trap_type.h"

class World;
class Entity;

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

    virtual TrapType getTrapType() = 0;
    virtual void trigger(Entity* entity, World* world) = 0;

    bool isArmed() const { return armed; }
    bool isRevealed() const { return revealed; }

    void reveal() { revealed = true; }
    void disable() { armed = false; }
};