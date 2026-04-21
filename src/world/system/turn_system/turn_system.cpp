#include "turn_system.h"
#include "../../world.h"
#include "../../entity/entity.h"
#include "../../entity/creature/player.h"
#include "../../entity/creature/monster.h"

#include <iostream>

//private:
bool TurnSystem::handleMove(Player* player, const Action& action) {
    return player->tryMove(action.dx, action.dy);
}

bool TurnSystem::handleWait(Player* player) {
    return true;
}

bool TurnSystem::handleUseItem(Player* player, const Action& action) {
    // player->useItem(action.itemId);
    return true;
}

//public:
TurnSystem::TurnSystem(World* world) : world(world) {}

void TurnSystem::processTurn(const Action& action) {
    if(isProcessing()) return;

    Player* player = getWorld()->getPlayer();
    if (!player || !player->isAlive()) {
        std::cout << "ban da thua " << std::endl;
        return;
    }

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
    if(!success) return;
    player->takeTurn();
    phase = TurnPhase::PLAYER;
}

void TurnSystem::update(float dt) {
    switch(phase) {
        case TurnPhase::IDLE: {
            getWorld()->getPlayer()->update(dt);
            for(Monster* e : getWorld()->getMonsters()) {
                e->update(dt);
            }
            break;
        }

        case TurnPhase::PLAYER: {
            getWorld()->getPlayer()->update(dt);
            if(getWorld()->getPlayer()->isEndTurn()) {
                monsterIndex = 0;
                phase = TurnPhase::ENEMY;
            }
            break;
        }

        case TurnPhase::ENEMY: {
            std::vector<Monster*> enemies = getWorld()->getMonsters();
            if(monsterIndex >= enemies.size()) {
                phase = TurnPhase::CLEAR;
                break;
            }

            Monster* m = enemies[monsterIndex];
            if(!m->hasStartedTurn()) m->takeTurn();
            m->update(dt);
            if(m->isEndTurn()) ++monsterIndex;

            break;
        }
        
        case TurnPhase::CLEAR: {
            getWorld()->removeDeadEntities();
            phase = TurnPhase::IDLE;
            break;
        }
        default:
            break;
    }
}
