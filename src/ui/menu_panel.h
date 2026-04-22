#pragma once
#include "raylib.h"

class MenuPanel {
private:
    bool visible = false;

public:
    void update();
    void render();
};