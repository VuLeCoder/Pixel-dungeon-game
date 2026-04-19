#pragma once

#include "creature.h"
#include "../hero_type.h"
#include "../../system/action.h"

class Player : public Creature{
private:
    static constexpr int PLAYER_WIDTH = 10, PLAYER_HEIGHT = 14;

    int numberKey = 0;
    int satietyTurns = 500;

public:
    Player(float x, float y, World* world, HeroType hero, Direction dir, int hp);
    
    bool isPlayer() const override { return true; }
    bool hasKey() const { return numberKey > 0; }
    
    void update(float dt) override;
    
    bool getAction(Action& action);
    void fall() override;
    void attack(Entity* target) override;
    void takeTurn() override;
};