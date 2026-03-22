#pragma once

#include <vector>
#include "level/level.h"
// #include "camera/camera.h"
#include "entity/creature/player.h"

class World {
private:
    int currLevel;
    std::vector<Level> levels;

    Player player;
    // Camera camera;

    void LoadLevel();

public:
    void init(HeroType type);

    Player getPlayer();

    void update();
    void render();

    void goToNextLevel();
    void goToPreviousLevel();

    Entity* getEntityAt(Position pos);
    void spawnMonsterNear(Position pos);
    void wakeUpAllMonsters();
    Position getRandomFreeTile();
};