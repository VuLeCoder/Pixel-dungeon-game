#include "monster.h"
#include "../../../engine/asset_manager.h"
#include "../../world.h"
#include "../../system/turn_system/turn_system.h"
#include "./../../system/AI/monster_ai.h"
#include "./../../system/FOV/fov_system.h"

#include <iostream>

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

void Monster::update(float dt) {
    Creature::update(dt);
}


void Monster::fall() {}

Vector2 Monster::canSeePlayer() const {
    int visionRange = getStats().visionRange;
    Vector2 currPos = getPosition();
    Vector2 playerPos = getWorld()->getPlayer()->getPosition();

    float dx = (playerPos.x - currPos.x) / TILE_SIZE;
    float dy = (playerPos.y - currPos.y) / TILE_SIZE;
    float distSq = dx * dx + dy * dy;

    if(distSq > visionRange * visionRange) {
        return {-1, -1};
    }
    
    if(!FOVSystem::MonsterHasLineOfSight(getWorld()->getCurrLevel(), currPos)) {
        return {-1, -1};
    }
    
    return playerPos;
}

void Monster::attack(Entity* target) {
    setState(ActionState::ATTACKING);
    std::cout << "Monster tan cong " << std::endl;
    int dame = GetRandomValue(getStats().minDame, getStats().minDame);
    target->takeDamage(dame);
}

void Monster::takeTurn() {
    Creature::takeTurn();
    ai->takeTurn();
}

void Monster::takeDamage(int damage) {
    Creature::takeDamage(damage);
    std::cout << "Monster bi danh" <<std::endl;
}
