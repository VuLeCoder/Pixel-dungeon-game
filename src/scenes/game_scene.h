#ifndef GAME_SCENE_H
#define GAME_SCENE_H

#include "scene.h"
#include "../world/entity/hero_type.h"

class IdleScene;
class World;
class UIManager;

class GameScene : public Scene {
private:
    IdleScene* idleScene;
    HeroType hero;
    World* world;
    UIManager* ui;

public:
    GameScene(HeroType hero);
    void Init();
    void Update();
    void Draw();
};

#endif