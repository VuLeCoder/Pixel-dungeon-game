#include "scene_manager.h"

Scene* SceneManager::currScene = nullptr;

void SceneManager::Init(Scene* scene) {
    currScene = scene;
    currScene->Init();
}

void SceneManager::ChangeScene(Scene* scene) {
    if(currScene != nullptr) {
        delete currScene;
    }

    currScene = scene;
    currScene->Init();
}

void SceneManager::Update() {
    if(currScene) {
        currScene->Update();
    }
}

void SceneManager::Draw() {
    if(currScene) {
        currScene->Draw();
    }
}