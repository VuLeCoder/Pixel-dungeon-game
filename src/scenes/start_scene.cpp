#include "../engine/scene_manager.h"
#include "../engine/asset_manager.h"

#include "start_scene.h"
#include "hero_select_scene.h"

#include "raylib.h"

void StartScene::Init() {
    SetWindowSize(1200, 700);
    startPng = AssetManager::GetTexture(AssetManager::START_SCENE);
    stairsRect = {446, 312, 75, 75};
}

void StartScene::Update() {
    Vector2 mouse = GetMousePosition();

    if(!IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
        return;
    }

    if (CheckCollisionPointRec(mouse, stairsRect)) {
        SceneManager::ChangeScene(new HeroSelectScene());
    }
}

void StartScene::Draw() {
    DrawTexture(startPng, 0, 0, WHITE);
}
