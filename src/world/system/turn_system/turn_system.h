#pragma once

#include "../action.h"

class World;
class Player;

class TurnSystem {
private:
    World* world;
    bool processing = false;

public:
    TurnSystem(World* world);

    World* getWorld() const { return world; }
    bool isProcessing() const;
    void processTurn(const Action& action);

    bool handleMove(Player* player, const Action& action);
    bool handleWait(Player* player);
    bool handleUseItem(Player* player, const Action& action);
};
