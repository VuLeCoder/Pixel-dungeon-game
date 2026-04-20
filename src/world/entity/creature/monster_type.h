#pragma once
#include "stats.h"
#include <string>

struct MonsterInfo{
    std::string name;
    Stats stats;
};

static const MonsterInfo RAT = {
    "rat",
    { 8, 1, 3, 0, 1, 6 }
};

static const MonsterInfo GNOLL = {
    "gnoll",
    { 12, 4, 8, 1, 3, 8 }
};

static const MonsterInfo CRAB = {
    "crab",
    { 18, 2, 4, 4, 8, 5 }
};
