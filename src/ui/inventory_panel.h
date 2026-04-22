#pragma once
#include "raylib.h"
#include <array>

class Player;

class InventoryPanel {
private:
    Player* player;
    bool visible = false;

    Texture2D weaponNone, armorNone, ringNone;

    static Vector2 equipItem[3];
    static Vector2 inventoryItem[15];
    static constexpr int textPos = 3;

    void renderNone(float scale);
    void renderEquipedItem(float scale);
    void renderInventoryItem(float scale);

public:
    InventoryPanel(Player* p);
    void update();
    void render(float scale);
};
