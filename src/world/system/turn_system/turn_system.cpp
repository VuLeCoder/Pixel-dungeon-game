#include "turn_system.h"
#include "../../world.h"
#include "../../entity/entity.h"
#include "../../entity/creature/player.h"
#include "../../entity/creature/monster.h"

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
        processing = false;
        return;
    }
// ========================= 1. Player action =========================
    switch(action.type) {
        case ActionType::MOVE:
            handleMove(player, action);
            break;

        case ActionType::WAIT:
            handleWait(player);
            break;

        case ActionType::USE_ITEM:
            handleUseItem(player, action);
            break;
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
    // world->updateEffects();
    // remove dead entities
    processing = false;
}

void TurnSystem::handleMove(Player* player, const Action& action) {
    player->tryMove(action.dx, action.dy);
}

void TurnSystem::handleWait(Player* player) {
    // intentionally empty
}

void TurnSystem::handleUseItem(Player* player, const Action& action) {
    // player->useItem(action.itemId);
}
