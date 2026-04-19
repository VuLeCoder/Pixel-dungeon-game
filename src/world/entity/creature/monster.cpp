#include "monster.h"
#include "../../../engine/asset_manager.h"
#include "../../world.h"
#include "../../system/turn_system/turn_system.h"

//private:
void attack(Entity* target) {

}

//public:
Monster::Monster(float x, float y, World* world, Direction dir, int hp)
    : Creature(x, y, world, dir, hp)
{
    anims[(int)AnimType::IDLE] = AssetManager::GetAnimation("rat_idle");
    anims[(int)AnimType::WALK] = AssetManager::GetAnimation("rat_walk");

    setAnimation(AnimType::IDLE);
}


void Monster::fall() {}

void Monster::takeTurn() {}

void Monster::update(float dt) {
    Creature::update(dt);
}
