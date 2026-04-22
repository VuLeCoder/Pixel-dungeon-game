#pragma once
#include "./../stats.h"
#include "./item_index.h"

#include <string>

enum class EffectType {
    NONE,
    ATE,
    HEAL,
    BUFF_STRENGTH,
    BUFF_ATTACK,
    BUFF_DEFENSE,
    INCREASE_VISION,
    TELEPORT,

    IDENTIFY,
    FLEE
};

struct Effect {
    EffectType type;
    int value; // ăn thì hồi bao lượt no hoặc uống thuốc hồi bao nhiêu máu
    int duration;
};

struct ItemStats : public Stats {
    int strength_required;
};

struct ItemType {
    std::string_view name;

    ItemCategory category;

    ItemStats stats;
    Effect effect;

    int value;
    bool stackable;
};
