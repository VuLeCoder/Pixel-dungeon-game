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

    bool changeFloor = true;

    TurnSystem* turnSystem;
    Player* player;
    FOVSystem* fovSystem;
    MyCamera camera;

    void LoadLevel();
    void initPlayer(HeroType heroType);
    void updateLevel(float dt);

public:
    World(HeroType heroType);
    void update();
    void render();
    
    void goToNextLevel();
    void goToPreviousLevel();
    bool isChangeFloor() const { return changeFloor; };
    void changeFloorDone() { changeFloor = false; };

    Level* getCurrLevel() const { return levels[currLevel]; }
    int getCurrFloor() const { return currLevel + 1; }

    TurnSystem* getTurnSystem() const  { return turnSystem; }
    Player* getPlayer() const  { return player; }
    std::vector<Monster*>& getMonsters();

    Entity* getEntityAtTile(int x, int y);
    void spawnMonsterNear(Vector2 pos);
    void wakeUpAllMonsters(Vector2 pos, int alarmRange);
    Vector2 getRandomFreeTile();

    void openDoor(int x, int y);
    bool isDoor(int x, int y) const;
    bool isPassable(int x, int y) const;
    void onEnter(Entity* e, int x, int y);
    void onLeft(int x, int y);
    void removeDeadEntities();
};
