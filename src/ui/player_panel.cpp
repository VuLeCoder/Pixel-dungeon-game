#include "ui_manager.h"
#include "./../engine/asset_manager.h"
#include "./../world/world.h"
#include "./../world/entity/creature/player.h"

//private:
void PlayerPanel::renderMainPanel(float scale) {
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
        {0, 0},
        0.0f,
        WHITE
    );

    DrawTextureEx(avaPlayer, {1210 + 3 * scale, 4 * scale}, 0.0f, scale, WHITE);
}

void PlayerPanel::renderHPBar(float scale) {
    int maxHP = player->getStats().maxHP;
    int currHP = player->getCurrHP();
    float ratio = static_cast<float>(currHP) / maxHP;

    float width = hpBarPng.width * ratio;
    float height = hpBarPng.height;
    DrawTexturePro(
        hpBarPng,
        {0, 0, width, height},
        {1210 + 30 * scale, 3 * scale, width * scale, height * scale },
        {0, 0},
        0.0f,
        WHITE
    );
    
    std::string hpText = std::to_string(currHP) + "/" + std::to_string(maxHP);
    int fontSize = 5;
    DrawText(
        hpText.c_str(),
        1210 + 49 * scale, 3 * scale,
        fontSize, WHITE
    );
}

void PlayerPanel::renderNumber(float scale) {
    int floor = player->getWorld()->getCurrFloor();
    int numberKey = player->getNumberKey();

    int fontSize = (int)(6 * scale);

    std::string floorText = std::to_string(floor);
    std::string keyText = std::to_string(numberKey);

    float baseX = 1210.0f;

    Vector2 floorPos = {
        baseX + 42.0f * scale,
        10.0f * scale
    };

    Vector2 keyPos = {
        baseX + 65.0f * scale,
        10.0f * scale
    };

    DrawText(floorText.c_str(), (int)floorPos.x, (int)floorPos.y, fontSize, WHITE);
    DrawText(keyText.c_str(), (int)keyPos.x, (int)keyPos.y, fontSize, WHITE);
}

//public:
PlayerPanel::PlayerPanel(Player * p) : player(p) {
    panePng = AssetManager::GetTexture(AssetManager::STATUS_PANE);
    avaPlayer = AssetManager::GetTexture(AssetManager::WARRIOR);
    hpBarPng = AssetManager::GetTexture(AssetManager::HP_BAR);
}

void PlayerPanel::update() {}

void PlayerPanel::render(float scale) {
    renderMainPanel(scale);
    renderHPBar(scale);
    renderNumber(scale);
}