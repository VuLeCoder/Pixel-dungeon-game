#ifndef HERO_SELECT_SCENE_H
#define HERO_SELECT_SCENE_H

#include "../world/entity/hero_type.h"

#include "scene.h"
#include <string>

class HeroSelectScene : public Scene {
private:
    Scene* next = nullptr;
    
    Texture2D selectPng, btnPng;
    Rectangle warriorRect, mageRect, exitBtnRect, startBtnRect;
    Vector2 warriorNamePoint, mageNamePoint;
    HeroType ht = HeroType::NONE;

public:
    void Init() override;
    void Update() override;
    void Draw() override;
};

#endif