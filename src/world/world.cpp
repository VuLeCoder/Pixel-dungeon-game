#include "world.h"
#include "./level/level.h"
#include "./system/turn_system/turn_system.h"

//private:



//public:
World::World(HeroType heroType) : camera(1200, 700, 33 * 16, 33 * 16) {
    init();
    player = new Player(16*9, 1+16*9, this, heroType, Direction::LEFT, 100);
    turnSystem = new TurnSystem(this);
}

void World::init() {
    currLevel = 0;
    
    Level* l1 = new Level(this);
    l1->generateMap(1);
    levels.push_back(l1);
}

void World::update() {
    float dt = GetFrameTime();

    levels[currLevel]->update();

    Action action;
    bool input = player->getAction(action);
    if(input) {
        turnSystem->processTurn(action);
    }

    player->update(dt);

    // camera.handleDrag();
    float wheel = GetMouseWheelMove();
    if (wheel != 0) {
        camera.updateZoom(wheel * 0.1f);
    }
    camera.followSmooth(player->getPosition(), GetFrameTime());
}

void World::render() {
    BeginScissorMode(0, 0, 1200, 700);
    camera.begin();

    levels[currLevel]->render();
    player->render();

    camera.end();
    EndScissorMode();
}

// =========== getter ===========
std::vector<Monster*>& World::getMonsters() {
    return levels[currLevel]->getMonsters();
}



// =========== level function ===========
bool World::isPassable(int x, int y) {
    return levels[currLevel]->isPassable(x, y);
}

void World::onEnter(Entity* e, int x, int y) {
    levels[currLevel]->onStep(e, y, x);
}

void World::onLeft(int x, int y) {
    levels[currLevel]->onLeft(y, x);
}

Vector2 World::getRandomFreeTile() {
    return levels[currLevel]->getRandomFreeTile();
}

Entity* World::getEntityAt(Vector2 pos) {
    levels[currLevel]->getEntityAt(pos);
}

void World::spawnMonsterNear(Vector2 pos) {}
void World::wakeUpAllMonsters() {}
