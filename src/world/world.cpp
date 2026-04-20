#include "world.h"
#include "./level/level.h"
#include "./system/turn_system/turn_system.h"
#include "./system/FOV/fov_system.h"

//private:
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
    init();

    Vector2 stairUpPos = getCurrLevel()->getStairUpPos();
    player = new Player(stairUpPos.x, stairUpPos.y + 1, this, heroType, Direction::LEFT);
    turnSystem = new TurnSystem(this);
    fovSystem = new FOVSystem();
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

    updateLevel(dt);

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

    getCurrLevel()->render();
    player->render();

    camera.end();
    EndScissorMode();
}

// =========== getter ===========
std::vector<Monster*>& World::getMonsters() {
    return getCurrLevel()->getMonsters();
}


// =========== level function ===========
bool World::isPassable(int x, int y) {
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

void World::wakeUpAllMonsters() {}
