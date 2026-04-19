#include "player.h"
#include "../../../engine/asset_manager.h"
#include "../../world.h"

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

void Player::fall() {

}

void Player::update(float dt) {
    switch(state) {
        case State::IDLE_STATE:
            setAnimation(AnimType::IDLE);
            break;

        case State::ACTION_STATE:
        {
            setAnimation(AnimType::WALK);

            if(targetPos.x > pos.x) {
                pos.x += SPEED * dt;
                if(pos.x > targetPos.x) pos.x = targetPos.x;
            } else if(targetPos.x < pos.x) {
                pos.x -= SPEED  * dt;
                if(pos.x < targetPos.x) pos.x = targetPos.x;
            }

            if(targetPos.y > pos.y) {
                pos.y += SPEED * dt;
                if(pos.y > targetPos.y) pos.y = targetPos.y;
            } else if(targetPos.y < pos.y) {
                pos.y -= SPEED * dt;
                if(pos.y < targetPos.y) pos.y = targetPos.y;
            }

            if(pos.x == targetPos.x && pos.y == targetPos.y) {
                state = State::IDLE_STATE;
            }

            break;
        }

        default:
            break;
    }
    currAnim->update(dt);
}

void Player::handleInput() {
    if (state != State::IDLE_STATE) return;

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

    if (keyCount != 1) return;

    targetPos = {
        pos.x + TILE_SIZE * dx,
        pos.y + TILE_SIZE * dy
    };

    int x = targetPos.x / TILE_SIZE;
    int y = targetPos.y / TILE_SIZE;
    if (!getWorld()->isPassable(y, x)) return;

    state = State::ACTION_STATE;
    getWorld()->onLeft(pos.x / TILE_SIZE, pos.y / TILE_SIZE);
    getWorld()->onEnter(this, x, y);

    // hướng nhìn
    if (dx > 0) dir = Direction::RIGHT;
    else if (dx < 0) dir = Direction::LEFT;
}

