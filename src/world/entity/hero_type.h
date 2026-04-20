#pragma once
#include "./creature/stats.h"

enum class HeroType {
    NONE,
    WARRIOR,
    MAGE
};

static constexpr Stats heroStats {
    25,
    1, 3,
    1, 1,
    6
};
