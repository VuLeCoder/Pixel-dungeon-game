#include "player.h"
#include "../../../engine/asset_manager.h"
#include "../../level/level.h"
#include "../../world.h"
#include "../../system/turn_system/turn_system.h"
#include "../../system/FOV/fov_system.h"
#include "../../system/inventory/inventory_system.h"

#include <string>
#include <cmath>

//private:

//public:
Player::Player(float x, float y, World* world, HeroType hero, Direction dir)
    : Creature(x, y, world, Direction::LEFT, heroBaseStats)
{
    setTargetPos(getPosition().x, getPosition().y);
    int size = world->getCurrLevel()->MAP_SIZE;
    playerVisible.resize(size, std::vector<bool>(size, false));

    anims[static_cast<int>(AnimType::IDLE)] = AssetManager::GetAnimation(
        std::string(AssetManager::WARRIOR) + "_" + std::string(AssetManager::IDLE)
    );

    anims[static_cast<int>(AnimType::WALK)] = AssetManager::GetAnimation(
        std::string(AssetManager::WARRIOR) + "_" + std::string(AssetManager::WALK)
    );

    anims[static_cast<int>(AnimType::ATK)] = AssetManager::GetAnimation(
        std::string(AssetManager::WARRIOR) + "_" + std::string(AssetManager::ATK)
    );
    anims[static_cast<int>(AnimType::ATK)].setRepeated(false);

    anims[static_cast<int>(AnimType::USE)] = AssetManager::GetAnimation(
        std::string(AssetManager::WARRIOR) + "_" + std::string(AssetManager::USE)
    );
    anims[static_cast<int>(AnimType::USE)].setRepeated(false);

    anims[static_cast<int>(AnimType::USE_SCROLL)] = AssetManager::GetAnimation(
        std::string(AssetManager::WARRIOR) + "_" + std::string(AssetManager::USE_SCROLL)
    );
    anims[static_cast<int>(AnimType::USE_SCROLL)].setRepeated(false);

    anims[static_cast<int>(AnimType::DEATH)] = AssetManager::GetAnimation(
        std::string(AssetManager::WARRIOR) + "_" + std::string(AssetManager::DEATH)
    );
    anims[static_cast<int>(AnimType::DEATH)].setRepeated(false);

    setAnimation(AnimType::IDLE);

    switch(hero) {
    case HeroType::WARRIOR:
        heroStats = warriorStats;
        break;
    
    default:
        heroStats = warriorStats;
        break;
    }

    inventorySystem = new InventorySystem();
}

bool Player::getAction(Action& action) {
    if (state != ActionState::IDLE) return false;

    int dx = 0;
    int dy = 0;
    int keyCount = 0;

    // hàng trên (Q W E)
    if (IsKeyPressed(KEY_Q)) { dx = -1; dy = -1; keyCount++; }
    if (IsKeyPressed(KEY_W)) { dx =  0; dy = -1; keyCount++; }
    if (IsKeyPressed(KEY_E)) { dx =  1; dy = -1; keyCount++; }

    // hàng giữa (A D)
    if (IsKeyPressed(KEY_A)) { dx = -1; dy =  0; keyCount++; }
    if (IsKeyPressed(KEY_D)) { dx =  1; dy =  0; keyCount++; }

    // hàng dưới (Z X C)
    if (IsKeyPressed(KEY_Z)) { dx = -1; dy =  1; keyCount++; }
    if (IsKeyPressed(KEY_X)) { dx =  0; dy =  1; keyCount++; }
    if (IsKeyPressed(KEY_C)) { dx =  1; dy =  1; keyCount++; }

    if (keyCount == 1) {
        action.type = ActionType::MOVE;
        action.dx = dx;
        action.dy = dy;
        return true;
    }

    // pickup
    keyCount = 0;
    if (IsKeyPressed(KEY_F)) { ++keyCount;}
    if(keyCount == 1) {
        action.type = ActionType::PICKUP_ITEM;
        return true;
    }

    // 👉 WAIT (rất quan trọng cho roguelike)
    keyCount = 0;
    if (IsKeyPressed(KEY_S)) { ++keyCount; }
    if(keyCount == 1) {
        action.type = ActionType::WAIT;
        return true;
    }

    return false;
}

void Player::attack(Entity* target) {
    setState(ActionState::ATTACKING);
    int dame = GetRandomValue(getStats().minDame, getStats().maxDame);
    target->takeDamage(dame);
}

void Player::fall() {}

void Player::takeTurn(bool isPlayerSeen) {
    Creature::takeTurn(true);
    updateFOV();
}

void Player::update(float dt) {
    Creature::update(dt);
}

void Player::updateFOV() {
    int x = getTargetPos().x / TILE_SIZE;
    int y = getTargetPos().y / TILE_SIZE;
    FOVSystem::computeInto(getWorld()->getCurrLevel(), x, y, getVisionRange(), playerVisible);
}


const std::vector<Item*>& Player::getInventory() const {
    return inventorySystem->getInventory();
}

const std::vector<Item*>& Player::getEquipedItem() const {
    return inventorySystem->getEquipedItem();
}

bool Player::pickup(Item* item) {
    if(!item) return false;
    return inventorySystem->add(item);
}

void Player::addStats(Stats statsAdd, HeroStats heroAdd) {
    Creature::addStats(statsAdd);

    heroStats.satietyTurns += heroAdd.satietyTurns;
    heroStats.satietyTurns = heroStats.satietyTurns < 600 ? heroStats.satietyTurns : 600;

    heroStats.strength += heroAdd.strength;
}

void Player::removeStats(Stats statsRemove, HeroStats heroRemove) {
    Creature::removeStats(statsRemove);

    heroStats.strength -= heroRemove.strength;
}

void Player::addKey() {
    ++numberKey;
}

void Player::useKey() {
    --numberKey;
}



