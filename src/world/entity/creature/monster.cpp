#include "monster.h"
#include "../../../engine/asset_manager.h"
#include "../../world.h"
#include "../../system/turn_system/turn_system.h"

//private:
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
Monster::Monster(float x, float y, World* world, Direction dir, const MonsterInfo type)
    : Creature(x, y, world, dir, type.stats)
{
    // anims[(int)AnimType::IDLE] = AssetManager::GetAnimation("rat_idle");
    // anims[(int)AnimType::WALK] = AssetManager::GetAnimation("rat_walk");

    // setAnimation(AnimType::IDLE);
}

void Monster::fall() {}

void Monster::attack(Entity* target) {
    int dame = GetRandomValue(getStats().minDame, getStats().minDame);
    target->takeDamage(dame);
}

void Monster::takeTurn() {
    int index = GetRandomValue(0, 7);
    tryMove((int)directions[index].x, (int)directions[index].y);
}

void Monster::update(float dt) {
    const int SPEED = 16.0f / 0.3f;
    switch(state) {
        case ActionState::IDLE:
            // setAnimation(AnimType::IDLE);
            break;

        case ActionState::MOVING:
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
                state = ActionState::IDLE;
            }

            break;
        }

        default:
            break;
    }
}

void Monster::render() {
    if(!isAlive()) return;
    Vector2 pos = getPosition();

    DrawRectangle(
        (int)pos.x,
        (int)pos.y,
        10,   // width
        14,   // height
        RED
    );
}
