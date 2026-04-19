#pragma once

#include <vector>
// #include "level/level.h"
#include "camera/camera.h"
#include "entity/creature/player.h"

class Level;
class Player;

class World {
private:
    int currLevel;
    std::vector<Level*> levels;

    Player* player;
    MyCamera camera;

    void LoadLevel();

public:
    World(HeroType heroType);

    void init();

    Player* getPlayer();

    void update();
    void render();

    void goToNextLevel();
    void goToPreviousLevel();

    Entity* getEntityAt(Vector2 pos);
    void spawnMonsterNear(Vector2 pos);
    void wakeUpAllMonsters();
    Vector2 getRandomFreeTile();


    bool isPassable(int x, int y);
    void onEnter(Entity* e, int x, int y);
    void onLeft(int x, int y);
};
