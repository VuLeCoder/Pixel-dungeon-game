#ifndef HERO_SELECT_SCENE_H
#define HERO_SELECT_SCENE_H

#include"../entities/hero.h"

#include "scene.h"
#include <string>

class HeroSelectScene : public Scene {
private:
    const std::string SCENE_HERO_SELECT_NAME = "hero_select_scene";
    const std::string START_BUTTON_NAME = "start_button";
    
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