#include "world.h"
#include "./level/level.h"
#include "./system/turn_system/turn_system.h"

//private:



//public:
World::World(HeroType heroType) : camera(1200, 700, 33 * 16, 33 * 16) {
    init();

    Vector2 stairUpPos = levels[currLevel]->getStairUpPos();
    player = new Player(stairUpPos.x, stairUpPos.y + 1, this, heroType, Direction::LEFT, 100);
    turnSystem = new TurnSystem(this);
}

void World::init() {
    currLevel = 0;
    
    Level* l1 = new Level(this);
    l1->generateMap(1);
    levels.push_back(l1);

    spawnMonsterNear({0, 0});
    spawnMonsterNear({0, 0});
}

void World::update() {
    float dt = GetFrameTime();

    levels[currLevel]->update(dt);

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
    camera.followSmooth(player->getPosition(), dt);
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
    levels[currLevel]->onStep(e, x, y);
}

void World::onLeft(int x, int y) {
    levels[currLevel]->onLeft(x, y);
}

Vector2 World::getRandomFreeTile() {
    return levels[currLevel]->getRandomFreeTile();
}

Entity* World::getEntityAtTile(int x, int y) {
    return levels[currLevel]->getEntityAtTile(x, y);
}

void World::spawnMonsterNear(Vector2 pos) {
    levels[currLevel]->spawnMonsterNear(pos); 
}

void World::wakeUpAllMonsters() {}
