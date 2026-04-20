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

void Monster::setTypeMonsterAnimation(const std::string& name) {
    anims[static_cast<int>(AnimType::IDLE)] = AssetManager::GetAnimation(
        std::string(name) + "_" + std::string(AssetManager::IDLE)
    );

    anims[static_cast<int>(AnimType::WALK)] = AssetManager::GetAnimation(
        std::string(name) + "_" + std::string(AssetManager::WALK)
    );

    anims[static_cast<int>(AnimType::ATK)] = AssetManager::GetAnimation(
        std::string(name) + "_" + std::string(AssetManager::ATK)
    );
    anims[static_cast<int>(AnimType::ATK)].setRepeated(false);

    anims[static_cast<int>(AnimType::DEATH)] = AssetManager::GetAnimation(
        std::string(name) + "_" + std::string(AssetManager::DEATH)
    );
    anims[static_cast<int>(AnimType::DEATH)].setRepeated(false);
}

//public:
Monster::Monster(float x, float y, World* world, Direction dir, const MonsterInfo type)
    : Creature(x, y, world, dir, type.stats)
{
    setTypeMonsterAnimation(type.name);
    setAnimation(AnimType::IDLE);
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
    Creature::update(dt);
}
