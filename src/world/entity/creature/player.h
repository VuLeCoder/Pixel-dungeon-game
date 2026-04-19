#pragma once

#include "creature.h"
#include "../hero_type.h"

class Player : public Creature{
private:
    static constexpr int PLAYER_WIDTH = 10, PLAYER_HEIGHT = 14;
    static constexpr float SPEED = 16.0f / 0.3f;

    int numberKey = 0;
    int satietyTurns = 500;

public:
    Player(float x, float y, World* world, HeroType hero, Direction dir, int hp);
    
    bool isPlayer() const override { return true; }
    bool hasKey() const { return numberKey > 0; }
    void fall() override;

    void update(float dt) override;

    void handleInput();
};