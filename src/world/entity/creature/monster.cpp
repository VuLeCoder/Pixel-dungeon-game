#include "monster.h"
#include "../../../engine/asset_manager.h"
#include "../../world.h"
#include "../../system/turn_system/turn_system.h"

#include <iostream>
//private:
void Monster::attack(Entity* target) {
    std::cout << "Monster attack" << std::endl;
}

std::vector<Vector2> Monster::directions = {
    { 0, -1 }, // UP
    { 1, -1 }, // UP-RIGHT
    { 1,  0 }, // RIGHT
    { 1,  1 }, // DOWN-RIGHT
    { 0,  1 }, // DOWN
    {-1,  1 }, // DOWN-LEFT
    {-1,  0 }, // LEFT
    {-1, -1 }  // UP-LEFT
};

//public:
Monster::Monster(float x, float y, World* world, Direction dir, int hp, MonsterType type)
    : Creature(x, y, world, dir, hp), type(type)
{
    // anims[(int)AnimType::IDLE] = AssetManager::GetAnimation("rat_idle");
    // anims[(int)AnimType::WALK] = AssetManager::GetAnimation("rat_walk");

    // setAnimation(AnimType::IDLE);
}

void Monster::fall() {}

void Monster::takeTurn() {
    int index = GetRandomValue(0, 7);
    tryMove((int)directions[index].x, (int)directions[index].y);
}

void Monster::update(float dt) {
    const int SPEED = 16.0f / 0.3f;
    switch(state) {
        case State::IDLE_STATE:
            // setAnimation(AnimType::IDLE);
            break;

        case State::ACTION_STATE:
        {
            // setAnimation(AnimType::WALK);

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
}

void Monster::render() {
    int px = getPosition().x;
    int py = getPosition().y;

    Color color = GREEN;
    if (type == MonsterType::C_RED) {
        color = RED;
    }

    // căn giữa trong tile 16x16
    int offsetX = (TILE_SIZE - 10) / 2;
    int offsetY = (TILE_SIZE - 14) / 2;

    DrawRectangle(
        px + offsetX,
        py + offsetY,
        10,
        14,
        color
    );
}
