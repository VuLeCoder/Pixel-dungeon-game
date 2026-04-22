#include "item_index.h"
#include "item_instance.h"
#include "item.h"

#include "./../../../engine/asset_manager.h"
#include "./../../world.h"
#include "./../creature/player.h"

#include <iostream>

//item_instance.h
ItemInstance::ItemInstance(const ItemType type) 
    : type(type)
{
    png = AssetManager::GetTexture(type.name);
}
// =========== =========== ===========

//item.h
Item::Item(
    float x, float y,
    World* world,
    const ItemType type
) : Entity(x, y, world)
{
    instance = new ItemInstance(type);
}

void Item::update(float dt) {}

void Item::render() {
    DrawTextureEx(instance->getTexture(), getPosition(), 0.0f, 1.0f, WHITE);
}

void Item::fall() {}

bool Item::isBlocking() const {
    return false;
}

void Item::takeDamage(int damage) {}

void Item::add() {
    
}

bool Item::use(Player* player) {
    if(!instance || !player) return false;
    
    const ItemType& type = instance->type;
    const Effect& effect = type.effect;

    switch(effect.type) {
        case EffectType::NONE: {
            player->addStats(type.stats, {0, effect.value});
            break;
        }

        case EffectType::ATE: {
            player->addStats(type.stats, {effect.value, 0});
            break;
        }

        case EffectType::HEAL: {
            player->heal(effect.value);
            break;
        }

        case EffectType::BUFF_STRENGTH: {
            player->addStats(type.stats, {0, effect.value});
            break;
        }

        case EffectType::TELEPORT: {
            Vector2 pos = getWorld()->getRandomFreeTile();
            player->setPos(pos.x, pos.y);
            player->setTargetPos(pos.x, pos.y + 1);
            break;
        }

        default:
            break;
    }

    if(type.stackable) {
        instance->use();
        if(instance->getQuantity() <= 0) {
            return true;
        }
        return false;
    }

    if(effect.type == EffectType::NONE) {
        player->equipItem(this);
        return false;
    }
    return true;

}



void Item::unequip() {
    if (!instance) return;
    
    const ItemType& type = instance->type;
    const Effect& effect = type.effect;
    
    Player* player = getWorld()->getPlayer();
    player->removeStats(type.stats, {0, effect.value});
}

// =========== =========== ===========






