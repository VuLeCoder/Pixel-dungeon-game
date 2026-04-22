#pragma once

#include "../action.h"

class World;
class Player;

enum class TurnPhase {
    IDLE,
    PLAYER,
    ENEMY,
    CLEAR
};

class TurnSystem {
private:
    World* world;
    TurnPhase phase = TurnPhase::IDLE;
    int monsterIndex;

    bool isProcessing() const { return phase != TurnPhase::IDLE; }

    bool handleMove(Player* player, const Action& action);
    bool handlePickupItem(Player* player);
    bool handleUseItem(Player* player, const Action& action);

public:
    TurnSystem(World* world);

    World* getWorld() const { return world; }
    void processTurn(const Action& action);
    void update(float dt);
};
