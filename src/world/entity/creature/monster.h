#pragma once

#include "./creature.h"

class Monster : public Creature{
private:
    void attack(Entity* target) override;

public:
    Monster(float x, float y, World* world, Direction dir, int hp);
        // : Creature(x, y, world, dir, hp);

    bool isPlayer() const override { return false; }
    
    void fall() override;
    void takeTurn() override;
    void update(float dt) override;
};
