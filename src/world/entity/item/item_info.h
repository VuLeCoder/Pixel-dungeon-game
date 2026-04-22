#pragma once
#include "item_type.h"

// === === weapon === ===
static constexpr itemType shortSword = {
    "Short_Sword",
    ItemCategory::WEAPON,
    { {0, 2, 4, 0, 0, 0}, 5 },
    { EffectType::NONE, 0, 0 },
    30,
    false
};

static constexpr itemType sword = {
    "Sword",
    ItemCategory::WEAPON,
    { {0, 4, 7, 0, 0, 0}, 7 },
    { EffectType::NONE, 0, 0 },
    80,
    false
};


// === === armor === ===
static constexpr itemType fabricArmor = {
    "Fabric Armor",
    ItemCategory::ARMOR,
    { {0, 0, 0, 1, 2, 0}, 5 },
    { EffectType::NONE, 0, 0 },
    15,
    false
};

static constexpr itemType leatherArmor = {
    "Leather Armor",
    ItemCategory::ARMOR,
    { {10, 0, 0, 2, 4, 0}, 6 },
    { EffectType::NONE, 0, 0 },
    60,
    false
};

static constexpr itemType chainArmor = {
    "Chain Armor",
    ItemCategory::ARMOR,
    { {15, 0, 0, 4, 6, -1}, 8 },
    { EffectType::NONE, 0, 0 },
    120,
    false
};


// === === ring === ===
static constexpr itemType ringOfVision = {
    "Ring_Vision",
    ItemCategory::RING,
    { {0, 0, 0, 0, 0, 2}, 0 },
    { EffectType::NONE, 0, 0 },
    100,
    false
};

static constexpr itemType ringOfDefense = {
    "Ring of Defense",
    ItemCategory::RING,
    { {0, 0, 0, 1, 3, 0}, 0 }, // buff def trực tiếp
    { EffectType::NONE, 0, 0 },
    120,
    false
};


// === === consumable === ===
static constexpr itemType bread = {
    "Bread",
    ItemCategory::FOOD,
    { {0, 0, 0, 0, 0, 0}, 0 }, 
    { EffectType::HEAL, 450, 0 },
    5,
    true
};

static constexpr itemType potionOfStrength = {
    "Potion of Strength",
    ItemCategory::POTION,
    { {0, 0, 0, 0, 0, 0}, 0},
    { EffectType::BUFF_STRENGTH, 1, 0 },
    40,
    true
};

static constexpr itemType healingPotion = {
    "Healing Potion",
    ItemCategory::POTION,
    { {0, 0, 0, 0, 0, 0}, 0 },
    { EffectType::HEAL, 25, 0 },
    20,
    true
};

static constexpr itemType scrollOfTeleport = {
    "Scroll_Teleport",
    ItemCategory::SCROLL,
    { {0, 0, 0, 0, 0, 0}, 0 },
    { EffectType::TELEPORT, 0, 0 },
    30,
    true
};

static constexpr itemType scrollOfAttack = {
    "Scroll_Attack",
    ItemCategory::SCROLL,
    { {0, 0, 0, 0, 0, 0}, 0 },
    { EffectType::BUFF_ATTACK, 3, 20 },
    35,
    true
};


// === === special === ===
static constexpr itemType gold = {
    "Gold",
    ItemCategory::GOLD,
    { {0, 0, 0, 0, 0, 0}, 0 },
    { EffectType::NONE, 0, 0 },
    10,
    true
};

static constexpr itemType key = {
    "Key",
    ItemCategory::KEY,
    { {0, 0, 0, 0, 0, 0}, 0 },
    { EffectType::NONE, 0, 0 },
    1,
    true
};
