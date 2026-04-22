#pragma once
#include "raylib.h"

class World;

class LogPanel {
private:
    World* world;

public:
    LogPanel(World* w) : world(w) {}
    void update();
    void render();
};
