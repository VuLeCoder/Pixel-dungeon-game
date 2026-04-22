#pragma once

#include "creature.h"
#include "../hero_type.h"
#include "../../system/action.h"

class Player : public Creature{
private:
    static constexpr int PLAYER_WIDTH = 10, PLAYER_HEIGHT = 14;

    std::vector<std::vector<bool>> playerVisible;

    HeroStats heroStats;
    int numberKey = 0;
    
public:
    Player(float x, float y, World* world, HeroType hero, Direction dir);
    
    bool isPlayer() const override { return true; }
    bool hasKey() const { return numberKey > 0; }
    int getNumberKey() const { return numberKey; }
    bool visible(int x, int y) const { return playerVisible[x][y]; }
    
    void update(float dt) override;
    void updateFOV();
    
    bool getAction(Action& action);
    int getVisionRange() const { return getStats().visionRange; }
    void fall() override;
    void attack(Entity* target) override;
    void takeTurn(bool isPlayerSeen) override;

};
