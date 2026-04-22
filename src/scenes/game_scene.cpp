#include "../engine/scene_manager.h"
#include "./start_scene.h"
#include "game_scene.h"

#include "raylib.h"
#include "../world/world.h"
#include "../ui/ui_manager.h"
#include "idle_scene.h"

GameScene::GameScene(HeroType type) : hero(type) {
    world = new World(hero);
    ui = new UIManager(world->getPlayer(), world);
    idleScene = new IdleScene();
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
    if(world->isChangeFloor()) {
        idleScene->update(GetFrameTime());
        if(idleScene->isEndIdle()) {
            world->changeFloorDone();
            idleScene->resetScnene();
        }
        return;
    }

    if(ui->isReturn()) {
        StartScene* sc = new StartScene();
        SceneManager::ChangeScene(sc);
        return;
    }

    world->update();
    ui->update();
}

void GameScene::Draw() {
    if(world->isChangeFloor()) {
        idleScene->render();
        return;
    }

    world->render();
    ui->render();
}
