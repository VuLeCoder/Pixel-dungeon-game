#include "turn_system.h"
#include "../../world.h"
#include "../../level/level.h"
#include "../../entity/entity.h"
#include "../../entity/creature/player.h"
#include "../../entity/creature/monster.h"
#include "./../../../utils/helper.h"

#include <iostream>

//private:
bool TurnSystem::handleMove(Player* player, const Action& action) {
    return player->tryMove(action.dx, action.dy);
}

bool TurnSystem::handlePickupItem(Player* player) {
    std::cout << " Toi dang nhat do " << std::endl;

    int x = player->getPosition().x / TILE_SIZE;
    int y = player->getPosition().y / TILE_SIZE;
    Item* item = getWorld()->getCurrLevel()->getItemAtTile(x, y);

    if(!item) return false;
    player->pickup(item);
    std::cout << " Nhat duoc roi " << std::endl;
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
            phase = TurnPhase::ENEMY;
            return;

        case ActionType::PICKUP_ITEM:
            success = handlePickupItem(player);
    
        case ActionType::USE_ITEM:
            success = handleUseItem(player, action);
            break;
    }
    if(!success) return;
    player->takeTurn(true);
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
            bool isPlayerSeen = distance(
                getWorld()->getPlayer()->getPosition(), 
                m->getPosition()
            ) <= getWorld()->getPlayer()->getVisionRange() + 2;

            if(!m->hasStartedTurn()) m->takeTurn(isPlayerSeen);
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
