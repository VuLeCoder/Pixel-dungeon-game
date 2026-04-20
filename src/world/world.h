#pragma once
#include "camera/camera.h"
#include "entity/creature/player.h"

#include <vector>

class Level;
class TurnSystem;
class Player;
class Monster;
class FOVSystem;

class World {
private:
    int currLevel;
    std::vector<Level*> levels;

    TurnSystem* turnSystem;
    Player* player;
    FOVSystem* fovSystem;
    MyCamera camera;

    void LoadLevel();
    void updateLevel(float dt);

public:
    World(HeroType heroType);
    void init();
    void update();
    void render();
    void goToNextLevel();
    void goToPreviousLevel();

    Level* getCurrLevel() const { return levels[currLevel]; }
    TurnSystem* getTurnSystem() const  { return turnSystem; }
    Player* getPlayer() const  { return player; }
    std::vector<Monster*>& getMonsters();

    Entity* getEntityAtTile(int x, int y);
    void spawnMonsterNear(Vector2 pos);
    void wakeUpAllMonsters();
    Vector2 getRandomFreeTile();
    bool isPassable(int x, int y);
    void onEnter(Entity* e, int x, int y);
    void onLeft(int x, int y);
};
