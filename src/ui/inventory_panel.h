#pragma once
#include "raylib.h"
#include <vector>

class Player;
class Item;

class InventoryPanel {
private:
    Player* player;
    bool visible = false;

    struct UISlot {
        Rectangle bounds;
        Item* item;
    };

    std::vector<UISlot> itemSlots;

    Texture2D weaponNone, armorNone, ringNone;

    static Vector2 EQUIP_ITEM_POS[3];
    static Vector2 INVENTORY_ITEM_POS[15];
    static constexpr int textPos = 3;

private:
    void renderNone(float scale);
    void renderEquipedItem(float scale);
    void renderInventoryItem(float scale);

public:
    InventoryPanel(Player* p);
    void update();
    void render(float scale);
};
