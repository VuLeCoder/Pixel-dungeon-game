#ifndef START_SCENE_H
#define START_SCENE_H

#include "scene.h"
#include <string>

class StartScene : public Scene {
private:
    Scene* next = nullptr;
    const std::string SCENE_START_NAME = "start_scene";
    Texture2D startPng;
    Rectangle stairsRect, rankingRect, itemRect, bagdeRect;

public:
    void Init() override;
    void Update() override;
    void Draw() override;
};

#endif