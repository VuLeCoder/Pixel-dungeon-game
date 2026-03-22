#ifndef GAME_SCENE_H
#define GAME_SCENE_H

#include "scene.h"
#include "../world/world.h"
#include "../ui/player_ui.h"
#include "../world/entity/hero_type.h"

class GameScene : public Scene {
private:
    HeroType hero;
    World world;
    PLayerUI ui;

public:
    GameScene(HeroType hero) : hero(hero) {}
    void Init();
    void Update();
    void Draw();
};

#endif