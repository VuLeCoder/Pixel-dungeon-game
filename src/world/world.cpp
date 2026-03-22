#include "world.h"

void World::init(HeroType type) {
    currLevel = 0;

    Level l1;
    l1.generateMap(1);
    levels.push_back(l1);
}

void World::update() {
    levels[currLevel].update();
}

void World::render() {
    levels[currLevel].render();
}
