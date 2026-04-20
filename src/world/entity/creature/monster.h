#pragma once

#include "./monster_type.h"
#include "./creature.h"

#include <vector>

class Monster : public Creature{
private:
    MonsterType type;
    static std::vector<Vector2> directions;

    void attack(Entity* target) override;

public:
    Monster(float x, float y, World* world, Direction dir, int hp, MonsterType type);
    
    bool isPlayer() const override { return false; }
    
    void fall() override;
    void takeTurn() override;
    void update(float dt) override;
    void render() override;
};
