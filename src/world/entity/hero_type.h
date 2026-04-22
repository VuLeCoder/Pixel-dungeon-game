#pragma once
#include "./stats.h"

enum class HeroType {
    NONE,
    WARRIOR,
    MAGE
};

static constexpr Stats heroBaseStats {
    25,
    1, 3,
    0, 1,
    6
};

struct HeroStats {
    int satietyTurns;
    int strength;
};

static constexpr HeroStats warriorStats {
    500,
    5
};
