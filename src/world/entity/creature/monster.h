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

    void update(float dt) override;
    bool isPlayer() const override { return false; }

    void attack(Entity* target) override;
    Vector2 canSeePlayer() const;
    void fall() override;
    void takeTurn() override;
    void takeDamage(int dame) override;
};
