#pragma once
#include "camera/camera.h"
#include "entity/creature/player.h"

#include <vector>

class Level;
class TurnSystem;
class Player;
class Monster;

class World {
private:
    int currLevel;
    std::vector<Level*> levels;

    TurnSystem* turnSystem;
    Player* player;
    MyCamera camera;

    void LoadLevel();

public:
    World(HeroType heroType);
    void init();
    void update();
    void render();
    void goToNextLevel();
    void goToPreviousLevel();

    TurnSystem* getTurnSystem() {return turnSystem; }
    Player* getPlayer() { return player; }
    std::vector<Monster*>& getMonsters();

    Entity* getEntityAt(Vector2 pos);
    void spawnMonsterNear(Vector2 pos);
    void wakeUpAllMonsters();
    Vector2 getRandomFreeTile();
    bool isPassable(int x, int y);
    void onEnter(Entity* e, int x, int y);
    void onLeft(int x, int y);
};
