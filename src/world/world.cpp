#include "world.h"
#include "./level/level.h"
#include "./system/turn_system/turn_system.h"
#include "./system/FOV/fov_system.h"

#include <iostream>

//private:
void World::LoadLevel() {
    Level* l1 = new Level(this);
    l1->generateMap(1);
    levels.push_back(l1);

    Level* l2 = new Level(this);
    l2->generateMap(2);
    levels.push_back(l2);

    Level* l3 = new Level(this);
    l3->generateMap(3);
    levels.push_back(l3);

    Level* l4 = new Level(this);
    l4->generateMap(2);
    levels.push_back(l4);

    Level* l5 = new Level(this);
    l5->generateMap(2);
    levels.push_back(l5);
}

void World::initPlayer(HeroType heroType) {
    currLevel = 0;
    player = new Player(0, 0, this, heroType, Direction::LEFT);

    currLevel = -1;
    goToNextLevel();
}

void World::updateLevel(float dt) {
    getCurrLevel()->update(dt);
    
    int px = player->getPosition().x / TILE_SIZE;
    int py = player->getPosition().y / TILE_SIZE;
    auto fov = FOVSystem::compute(getCurrLevel(), px, py, player->getVisionRange());

    for(int x=0; x<Level::MAP_SIZE; ++x) {
        for(int y=0; y<Level::MAP_SIZE; ++y) {
            if(fov.visible[x][y]) {
                getCurrLevel()->discover(x, y);
            }
        }
    }
}

//public:
World::World(HeroType heroType) : camera(1200, 700, 33 * 16, 33 * 16) {
    LoadLevel();
    std::cout << "hello Levels ";

    initPlayer(heroType);
    std::cout << "hello Player ";

    turnSystem = new TurnSystem(this);
    fovSystem = new FOVSystem();
    std::cout << "hello World ";

    spawnMonsterNear({0, 0});
}

void World::update() {
    float dt = GetFrameTime();

    updateLevel(dt);

    Action action;
    bool input = player->getAction(action);
    if(input) {
        turnSystem->processTurn(action);
    }
    turnSystem->update(dt);

    // camera.handleDrag();
    float wheel = GetMouseWheelMove();
    if (wheel != 0) {
        camera.updateZoom(wheel * 0.1f);
    }
    camera.followSmooth(player->getPosition(), dt);
}

void World::render() {
    BeginScissorMode(0, 0, 1200, 700);
    camera.begin();

    getCurrLevel()->render();
    player->render();

    camera.end();
    EndScissorMode();
}

void World::goToNextLevel() {
    ++currLevel;
    if(currLevel >= levels.size()) {
        currLevel = levels.size() - 1;
        std::cout << "Khong xuong duoc" <<std::endl;
        return;
    }

    Vector2 stairPos = getCurrLevel()->getStairUpPos();
    player->setPos(stairPos.x, stairPos.y + 1);
    player->setTargetPos(stairPos.x, stairPos.y + 1);
    player->updateFOV();
    changeFloor = true;
}

void World::goToPreviousLevel() {
    --currLevel;
    if(currLevel < 0) {
        currLevel = 0;
        std::cout << "Khong len duoc" <<std::endl;
        return;
    }

    Vector2 stairPos = getCurrLevel()->getStairDownPos();
    player->setPos(stairPos.x, stairPos.y + 1);
    player->setTargetPos(stairPos.x, stairPos.y + 1);
    player->updateFOV();
    changeFloor = true;
}


// =========== getter ===========
std::vector<Monster*>& World::getMonsters() {
    return getCurrLevel()->getMonsters();
}


// =========== level function ===========
bool World::isPassable(int x, int y) const {
    return getCurrLevel()->isPassable(x, y);
}

void World::onEnter(Entity* e, int x, int y) {
    getCurrLevel()->onStep(e, x, y);
}

void World::onLeft(int x, int y) {
    getCurrLevel()->onLeft(x, y);
}

Vector2 World::getRandomFreeTile() {
    return getCurrLevel()->getRandomFreeTile();
}

Entity* World::getEntityAtTile(int x, int y) {
    return getCurrLevel()->getEntityAtTile(x, y);
}

void World::spawnMonsterNear(Vector2 pos) {
    getCurrLevel()->spawnMonsterNear(pos); 
}

void World::removeDeadEntities() {
    getCurrLevel()->removeDeadEntities();
}

void World::wakeUpAllMonsters(Vector2 pos, int alarmRange) {
    getCurrLevel()->wakeUpAllMonsters(pos, alarmRange);
}
