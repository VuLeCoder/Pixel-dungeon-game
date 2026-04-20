#pragma once

#include "./monster_type.h"
#include "./creature.h"

#include <vector>

class Monster : public Creature{
private:
    MonsterInfo type;
    static std::vector<Vector2> directions;

public:
    Monster(float x, float y, World* world, Direction dir, const MonsterInfo type);
    
    bool isPlayer() const override { return false; }

    void attack(Entity* target) override;
    
    void fall() override;
    void takeTurn() override;
    void update(float dt) override;
    void render() override;
};
