#pragma once
#include "raylib.h"

class Player;

class PlayerPanel {
private:
    static Rectangle menuButton;
    static Vector2 textFloor, textKey;

    Player* player;
    Texture2D panePng;

public:
    PlayerPanel(Player* p);
    void update();
    void render();
};
