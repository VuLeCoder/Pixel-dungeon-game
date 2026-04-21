#include "monster.h"
#include "../../../engine/asset_manager.h"
#include "../../world.h"
#include "../../system/turn_system/turn_system.h"
#include "./../../system/AI/monster_ai.h"

//private:
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
    ai = new MonsterAI(this);
    setTypeMonsterAnimation(type.name);
    setAnimation(AnimType::IDLE);
}

Monster::~Monster() {
    delete ai;
    ai = nullptr;
}

void Monster::fall() {}

void Monster::attack(Entity* target) {
    int dame = GetRandomValue(getStats().minDame, getStats().minDame);
    target->takeDamage(dame);
}

void Monster::takeTurn() {
    if(state == ActionState::DEATH) return;
    ai->takeTurn();
}

void Monster::update(float dt) {
    Creature::update(dt);
}
