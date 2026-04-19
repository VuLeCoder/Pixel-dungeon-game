#include "player.h"
#include "../../../engine/asset_manager.h"
#include "../../world.h"
#include "../../system/turn_system/turn_system.h"

#include <iostream>
#include <string>
#include <cmath>

Player::Player(float x, float y, World* world, HeroType hero, Direction dir, int hp)
    : Creature(x, y, world, dir, hp)
{
    anims[static_cast<int>(AnimType::IDLE)] = AssetManager::GetAnimation(
        std::string(AssetManager::WARRIOR) + "_" + std::string(AssetManager::IDLE)
    );

    anims[static_cast<int>(AnimType::WALK)] = AssetManager::GetAnimation(
        std::string(AssetManager::WARRIOR) + "_" + std::string(AssetManager::WALK)
    );

    setAnimation(AnimType::IDLE);
}

bool Player::getAction(Action& action) {
    if (state != State::IDLE_STATE) return false;

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

    // 👉 WAIT (rất quan trọng cho roguelike)
    if (IsKeyPressed(KEY_SPACE)) {
        action.type = ActionType::WAIT;
        return true;
    }

    return false;
}

void Player::attack(Entity* target) {}
void Player::fall() {}
void Player::takeTurn() {}

void Player::update(float dt) {
    Creature::update(dt);
}
