#ifndef START_SCENE_H
#define START_SCENE_H

#include "scene.h"
#include "raylib.h"
#include <string>

class StartScene : public Scene {
private:
    Scene* next = nullptr;
    Texture2D startPng;
    Rectangle stairsRect, rankingRect, itemRect, bagdeRect;

public:
    void Init() override;
    void Update() override;
    void Draw() override;
};

#endif