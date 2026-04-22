#pragma once
#include "./stats.h"

enum class HeroType {
    NONE,
    WARRIOR,
    MAGE
};

static constexpr Stats heroStats {
    25,
    1, 3,
    0, 1,
    6
};
