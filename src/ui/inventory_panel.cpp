#include "./inventory_panel.h"
#include "./../engine/asset_manager.h"
#include "./../world/entity/creature/player.h"
#include "./../world/entity/item/item.h"
#include "./../world/entity/item/item_instance.h"

//private:
Vector2 InventoryPanel::EQUIP_ITEM_POS[3] = {
    {8, 42}, {20, 42}, {32, 42}
};
Vector2 InventoryPanel::INVENTORY_ITEM_POS[15] = {
    {44, 42}, {56, 42}, {68, 42},
    {8, 57}, {20, 57}, {32, 57}, {44, 57}, {56, 57}, {68, 57},
    {8, 72}, {20, 72}, {32, 72}, {44, 72}, {56, 72}, {68, 72}
};

void InventoryPanel::renderNone(float scale) {
    float pngScale = scale * 9 / 14;
    const std::vector<Item*>& items = player->getEquipedItem();

    if(!items[0])
        DrawTextureEx(
            weaponNone,
            { 1210 + EQUIP_ITEM_POS[0].x * scale, EQUIP_ITEM_POS[0].y * scale},
            0.0f, pngScale, WHITE
        );
    
    if(!items[1])
        DrawTextureEx(
            armorNone,
            { 1210 + EQUIP_ITEM_POS[1].x * scale, EQUIP_ITEM_POS[1].y * scale},
            0.0f, pngScale, WHITE
        );

    if(!items[2])
        DrawTextureEx(
            ringNone,
            { 1210 + EQUIP_ITEM_POS[2].x * scale, EQUIP_ITEM_POS[2].y * scale},
            0.0f, pngScale, WHITE
        );
}

void InventoryPanel::renderEquipedItem(float scale) {
    float pngScale = scale * 9 / 14;
    const std::vector<Item*>& items = player->getEquipedItem();
    
    for(int index=0; index<3; ++index) {
        if(!items[index]) continue;

        float x = 1210 + EQUIP_ITEM_POS[index].x * scale;
        float y = EQUIP_ITEM_POS[index].y * scale;

        DrawTextureEx(
            items[index]->getItemInstance()->getTexture(),
            { x, y },
            0.0f, pngScale, BLACK
        );
        DrawTextureEx(
            items[index]->getItemInstance()->getTexture(),
            { x, y },
            0.0f, pngScale, WHITE
        );

        Rectangle rect = { x, y, 11 * scale, 14 * scale };
        itemSlots.push_back({ rect, items[index] });
    }
}

void InventoryPanel::renderInventoryItem(float scale) {
    float pngScale = scale * 9 / 14;
    const std::vector<Item*>& items = player->getInventory();

    int index = 0;
    for(Item* i : items) {
        float x = 1210 + INVENTORY_ITEM_POS[index].x * scale;
        float y = INVENTORY_ITEM_POS[index].y * scale;

        DrawTextureEx(
            i->getItemInstance()->getTexture(),
            { x, y },
            0.0f, pngScale, WHITE
        );

        Rectangle rect = { x, y, 11 * scale, 14 * scale };
        itemSlots.push_back({ rect, i });

        ++index;
    }
}


//public:
InventoryPanel::InventoryPanel(Player* p) : player(p) {
    weaponNone = AssetManager::GetTexture(AssetManager::WEAPON_NONE);
    armorNone = AssetManager::GetTexture(AssetManager::ARMOR_NONE);
    ringNone = AssetManager::GetTexture(AssetManager::RING_NONE);
}

#include <iostream>
void InventoryPanel::update() {
    if(!player) return;

    if(IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
        Vector2 mouse = GetMousePosition();

        for(auto& slot : itemSlots) {
            if(CheckCollisionPointRec(mouse, slot.bounds)) {
                if(slot.item) {
                    std::cout << "hello" <<std::endl;
                    player->setPendingUseItem(slot.item);
                    break;
                }
            }
        }
    }
}

void InventoryPanel::render(float scale) {
    for(UISlot sl : itemSlots) {
        sl.item = nullptr;
    }
    itemSlots.clear();

    renderNone(scale);
    if(!player) return;

    renderEquipedItem(scale);
    renderInventoryItem(scale);
}
