#pragma once

enum class ActionType {
    MOVE,
    WAIT,
    USE_ITEM
};

struct Action {
    ActionType type;

    int dx = 0;
    int dy = 0;
    int itemId = -1;
};