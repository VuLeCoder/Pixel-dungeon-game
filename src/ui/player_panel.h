#pragma once
#include "raylib.h"

class Player;

class PlayerPanel {
private:
    static constexpr Rectangle menuButton = { 1210 + 86 * 5, 3 * 5, 12 * 5, 11 * 5};
    static Vector2 textFloor, textKey;

    Player* player;
    Texture2D panePng, hpBarPng, avaPlayer;

    void renderMainPanel(float scale);
    void renderHPBar(float scale);
    void renderNumber(float scale);

public:
    PlayerPanel(Player* p);
    void update();
    void render(float scale);
};
