#include "../engine/asset_manager.h"

#include "start_scene.h"
#include "hero_select_scene.h"

#include "raylib.h"

void StartScene::Init() {
    startPng = AssetManager::GetTexture(SCENE_START_NAME);
    stairsRect = {446, 312, 75, 75};
}

void StartScene::Update() {
    Vector2 mouse = GetMousePosition();

    if(!IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
        return;
    }

    if (CheckCollisionPointRec(mouse, stairsRect)) {
        // to hero select scene
    }
}

void StartScene::Draw() {
    DrawTexture(startPng, 0, 0, WHITE);
    // DrawRectangleRec(stairsRect, RED);
}