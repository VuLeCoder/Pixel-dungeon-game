#pragma once
#include "player_panel.h"
#include "log_panel.h"
#include "inventory_panel.h"
#include "menu_panel.h"

class UIManager {
private:
    Player* player;
    World* world;

    PlayerPanel playerPanel;
    InventoryPanel inventoryPanel;
    LogPanel logPanel;
    MenuPanel menuPanel;

    float scale = 5.0f;
    bool pauseGame = false;
    bool returnStart = false;

public:
    UIManager(Player* p, World* w)
        : player(p), world(w),
          playerPanel(p),
          inventoryPanel(p),
          logPanel(w),
          menuPanel() {}

    bool isPauseGame() const { return pauseGame == true; }
    bool isReturn() const { return returnStart == true; }

    void update() {
        returnStart = playerPanel.update();
        inventoryPanel.update();
        menuPanel.update();
    }

    void render() {
        playerPanel.render(scale);
        inventoryPanel.render(scale);
        logPanel.render(scale);
        menuPanel.render();
    }
};
