#pragma once
#include "./../../../engine/asset_manager.h"
#include "item_type.h"

// === === weapon === ===
static constexpr ItemType shortSword = {
    AssetManager::SHORT_SWORD,
    ItemCategory::WEAPON,
    { {0, 2, 4, 0, 0, 0}, 5 },
    { EffectType::NONE, 0, 0 },
    30,
    false
};

static constexpr ItemType sword = {
    AssetManager::SWORD,
    ItemCategory::WEAPON,
    { {0, 4, 7, 0, 0, 0}, 7 },
    { EffectType::NONE, 0, 0 },
    80,
    false
};


// === === armor === ===
static constexpr ItemType fabricArmor = {
    AssetManager::FABRIC_ARMOR,
    ItemCategory::ARMOR,
    { {0, 0, 0, 1, 2, 0}, 5 },
    { EffectType::NONE, 0, 0 },
    15,
    false
};

static constexpr ItemType leatherArmor = {
    AssetManager::LEATHER_ARMOR,
    ItemCategory::ARMOR,
    { {10, 0, 0, 2, 4, 0}, 6 },
    { EffectType::NONE, 0, 0 },
    60,
    false
};

static constexpr ItemType chainArmor = {
    AssetManager::CHAIN_ARMOR,
    ItemCategory::ARMOR,
    { {15, 0, 0, 4, 6, -1}, 8 },
    { EffectType::NONE, 0, 0 },
    120,
    false
};


// === === ring === ===
static constexpr ItemType ringOfVision = {
    AssetManager::RING_VISION,
    ItemCategory::RING,
    { {0, 0, 0, 0, 0, 2}, 0 },
    { EffectType::NONE, 0, 0 },
    100,
    false
};

static constexpr ItemType ringOfDefense = {
    AssetManager::RING_DEFENSE,
    ItemCategory::RING,
    { {0, 0, 0, 1, 3, 0}, 0 }, // buff def trực tiếp
    { EffectType::NONE, 0, 0 },
    120,
    false
};


// === === consumable === ===
static constexpr ItemType bread = {
    AssetManager::BREAD,
    ItemCategory::FOOD,
    { {0, 0, 0, 0, 0, 0}, 0 }, 
    { EffectType::ATE, 450, 0 },
    5,
    true
};

static constexpr ItemType potionOfStrength = {
    AssetManager::POTION_STRENGTH,
    ItemCategory::POTION,
    { {0, 0, 0, 0, 0, 0}, 0},
    { EffectType::BUFF_STRENGTH, 1, 0 },
    40,
    true
};

static constexpr ItemType healingPotion = {
    AssetManager::POTION_HEALING,
    ItemCategory::POTION,
    { {0, 0, 0, 0, 0, 0}, 0 },
    { EffectType::HEAL, 25, 0 },
    20,
    true
};

static constexpr ItemType scrollOfTeleport = {
    AssetManager::SCROLL_TELEPORT,
    ItemCategory::SCROLL,
    { {0, 0, 0, 0, 0, 0}, 0 },
    { EffectType::TELEPORT, 0, 0 },
    30,
    true
};

static constexpr ItemType scrollOfAttack = {
    AssetManager::SCROLL_ATTACK,
    ItemCategory::SCROLL,
    { {0, 0, 0, 0, 0, 0}, 0 },
    { EffectType::BUFF_ATTACK, 3, 20 },
    35,
    true
};


// === === special === ===
static constexpr ItemType gold = {
    AssetManager::GOLD_ITEM,
    ItemCategory::GOLD_ITEM,
    { {0, 0, 0, 0, 0, 0}, 0 },
    { EffectType::NONE, 0, 0 },
    10,
    true
};

static constexpr ItemType key = {
    AssetManager::KEY,
    ItemCategory::KEY,
    { {0, 0, 0, 0, 0, 0}, 0 },
    { EffectType::NONE, 0, 0 },
    1,
    true
};
