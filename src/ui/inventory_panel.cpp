#include "./inventory_panel.h"
#include "./../engine/asset_manager.h"
#include "./../world/entity/creature/player.h"
#include "./../world/entity/item/item.h"
#include "./../world/entity/item/item_instance.h"

//private:
Vector2 InventoryPanel::equipItem[3] = {
    {8, 42}, {20, 42}, {32, 42}
};
Vector2 InventoryPanel::inventoryItem[15] = {
    {44, 42}, {56, 42}, {68, 42},
    {8, 57}, {20, 57}, {32, 57}, {44, 57}, {56, 57}, {68, 57},
    {8, 72}, {20, 72}, {32, 72}, {44, 72}, {56, 72}, {68, 72}
};

void InventoryPanel::renderNone(float scale) {
    float pngScale = scale * 9 / 14;

    DrawTextureEx(
        weaponNone,
        { 1210 + equipItem[0].x * scale, equipItem[0].y * scale},
        0.0f, pngScale, WHITE
    );
    DrawTextureEx(
        armorNone,
        { 1210 + equipItem[1].x * scale, equipItem[1].y * scale},
        0.0f, pngScale, WHITE
    );
    DrawTextureEx(
        ringNone,
        { 1210 + equipItem[2].x * scale, equipItem[2].y * scale},
        0.0f, pngScale, WHITE
    );
}

void InventoryPanel::renderEquipedItem(float scale) {
}

void InventoryPanel::renderInventoryItem(float scale) {
    std::vector<Item*> items = player->getInventory();
    float pngScale = scale * 9 / 14;

    int index = 0;
    for(Item* i : items) {
        DrawTextureEx(
            i->getItemInstance()->getTexture(),
            { 1210 + inventoryItem[index].x * scale, inventoryItem[index].y * scale},
            0.0f, pngScale, WHITE
        );
        ++index;
    }
}


//public:
InventoryPanel::InventoryPanel(Player* p) : player(p) {
    weaponNone = AssetManager::GetTexture(AssetManager::WEAPON_NONE);
    armorNone = AssetManager::GetTexture(AssetManager::ARMOR_NONE);
    ringNone = AssetManager::GetTexture(AssetManager::RING_NONE);
}

void InventoryPanel::update() {}

void InventoryPanel::render(float scale) {
    renderNone(scale);
    if(!player) return;

    renderEquipedItem(scale);
    renderInventoryItem(scale);
}