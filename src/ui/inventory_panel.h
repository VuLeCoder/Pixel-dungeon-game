#pragma once
#include "raylib.h"

class Player;

class InventoryPanel {
private:
    Player* player;
    bool visible = false;

public:
    InventoryPanel(Player* p) : player(p) {}
    void update();
    void render();
};
