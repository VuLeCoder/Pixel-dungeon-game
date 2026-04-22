#include "ui_manager.h"
#include "./../engine/asset_manager.h"
#include "./../world/world.h"
#include "./../world/entity/creature/player.h"

PlayerPanel::PlayerPanel(Player * p) : player(p) {
    panePng = AssetManager::GetTexture(AssetManager::STATUS_PANE);
}



void PlayerPanel::update() {}
void InventoryPanel::update() {}
void LogPanel::update() {}
void MenuPanel::update() {}

void PlayerPanel::render() {
    float scale = 5.0f;

    Rectangle src = {
        0, 0,
        (float)panePng.width,
        (float)panePng.height
    };

    Rectangle dst = {
        1210.0f, 0.0f,
        panePng.width * scale,
        panePng.height * scale
    };

    DrawTexturePro(
        panePng,
        src,
        dst,
        {0, 0},   // origin (top-left)
        0.0f,     // rotation
        WHITE
    );
}

void InventoryPanel::render() {}
void LogPanel::render() {}
void MenuPanel::render() {}


