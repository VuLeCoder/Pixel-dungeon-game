#pragma once

#include "./monster_type.h"
#include "./creature.h"

#include <vector>

class MonsterAI;

class Monster : public Creature{
private:
    MonsterInfo type;

    MonsterAI* ai;

    void setTypeMonsterAnimation(const std::string& name);

public:
    Monster(float x, float y, World* world, Direction dir, const MonsterInfo type);
    ~Monster();

    bool isPlayer() const override { return false; }

    void attack(Entity* target) override;
    
    void fall() override;
    void takeTurn() override;
    void update(float dt) override;
};
