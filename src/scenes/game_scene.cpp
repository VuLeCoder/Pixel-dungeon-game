#include "game_scene.h"
#include "raylib.h"
#include "../world/world.h"
#include "../ui/ui_manager.h"

GameScene::GameScene(HeroType type) : hero(hero) {
    world = new World(hero);
    ui = new UIManager(world->getPlayer(), world);
}

void GameScene::Init() {
    SetWindowSize(1710, 700);
    int monitor = GetCurrentMonitor();
    int monitorWidth = GetMonitorWidth(monitor);
    int monitorHeight = GetMonitorHeight(monitor);

    int posX = (monitorWidth - 1710) / 2;
    int posY = (monitorHeight - 700) / 2;

    SetWindowPosition(posX, posY);
}

void GameScene::Update() {
    world->update();
    // ui.update();
}

void GameScene::Draw() {
    world->render();
    ui->render();
}