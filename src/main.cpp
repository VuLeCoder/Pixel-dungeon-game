#include "raylib.h"

#include "engine/asset_manager.h"
#include "engine/scene_manager.h"

#include "scenes/start_scene.h"

constexpr int WINDOW_WIDTH = 1200;
constexpr int WINDOW_HEIGHT = 700;

int main() {

    InitWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "Pixel Dungeon");
    AssetManager::Load();

    SetTargetFPS(60);

    SceneManager::Init(new StartScene());

    while (!WindowShouldClose()) {

        SceneManager::Update();

        BeginDrawing();
        ClearBackground(BLACK);

        SceneManager::Draw();

        EndDrawing();
    }

    AssetManager::Unload();
    CloseWindow();
}