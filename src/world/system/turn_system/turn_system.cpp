#include "turn_system.h"
#include "../../world.h"
#include "../../entity/entity.h"
#include "../../entity/creature/player.h"
#include "../../entity/creature/monster.h"

#include <iostream>

TurnSystem::TurnSystem(World* world)
    : world(world) {}

bool TurnSystem::isProcessing() const {
    return processing;
}

void TurnSystem::processTurn(const Action& action) {
    if (processing) return;
    processing = true;

    Player* player = getWorld()->getPlayer();
    if (!player || !player->isAlive()) {
        std::cout << "ban da thua " << std::endl;
        processing = false;
        return;
    }
// ========================= 1. Player action =========================
    bool success = false;
    switch(action.type) {
        case ActionType::MOVE:
            success = handleMove(player, action);
            break;

        case ActionType::WAIT:
            success = handleWait(player);
            break;

        case ActionType::USE_ITEM:
            success = handleUseItem(player, action);
            break;
    }
    if(!success) {
        processing = false;
        return;
    }
    player->takeTurn();

    if (!player->isAlive()) {
        processing = false;
        return;
    }
// ========================= ========================= =========================
// ========================= 2. Enemy turn =========================
    std::vector<Monster*> enemies = getWorld()->getMonsters();
    for(Monster* e : enemies) {
        e->takeTurn();
    }

    if (!player->isAlive()) {
        processing = false;
        return;
    }
// ========================= ========================= =========================
    processing = false;
}

bool TurnSystem::handleMove(Player* player, const Action& action) {
    return player->tryMove(action.dx, action.dy);
}

bool TurnSystem::handleWait(Player* player) {
    return true;
}

bool TurnSystem::handleUseItem(Player* player, const Action& action) {
    // player->useItem(action.itemId);
}
