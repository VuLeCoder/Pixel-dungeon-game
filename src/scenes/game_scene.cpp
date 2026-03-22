#include "game_scene.h"
#include "raylib.h"

void GameScene::Init() {
    SetWindowSize(1700, 700);

    world.init(hero);
    // ui.init(world.getPlayer());
}

void GameScene::Update() {
    world.update();
    // ui.update();
}

void GameScene::Draw() {
    world.render();
}