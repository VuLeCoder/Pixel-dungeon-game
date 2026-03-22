#include "../engine/asset_manager.h"
#include "../engine/scene_manager.h"

#include "start_scene.h"
#include "hero_select_scene.h"
#include "game_scene.h"

#include "raylib.h"

void HeroSelectScene::Init() {
    selectPng = AssetManager::GetTexture(SCENE_HERO_SELECT_NAME);
    btnPng = AssetManager::GetTexture(START_BUTTON_NAME);

    exitBtnRect = {1125, 16, 45, 36};
    startBtnRect = {355, 430, 512, 96};

    warriorRect = {490, 270, 82, 112};
    warriorNamePoint = {480, 390};

    mageRect = {622, 278, 73, 104};
    mageNamePoint = {620, 390};
}

void HeroSelectScene::Update() {
    Vector2 mouse = GetMousePosition();

    if(!IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
        return;
    }

    if(CheckCollisionPointRec(mouse, exitBtnRect)) {
        SceneManager::ChangeScene(new StartScene());
    }
    
    if(CheckCollisionPointRec(mouse, warriorRect)) {
        ht = HeroType::WARRIOR;
    }
    if(CheckCollisionPointRec(mouse, mageRect)) {
        ht = HeroType::MAGE;
    }

    if(ht == HeroType::NONE) {
        return;
    }
    if(CheckCollisionPointRec(mouse, startBtnRect)) {
        SceneManager::ChangeScene(new GameScene(ht));
    }
}

void HeroSelectScene::Draw() {
    DrawTexture(selectPng, 0, 0, WHITE);
    if(ht != HeroType::NONE) {
        DrawTexture(btnPng, (int)startBtnRect.x, (int)startBtnRect.y, WHITE);
        
        if(ht == HeroType::WARRIOR) {
            DrawText("WARRIOR", warriorNamePoint.x, warriorNamePoint.y, 20, WHITE);
        } else {
            DrawText("MAGE", mageNamePoint.x, mageNamePoint.y, 20, WHITE);
        }
    }
}