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

public:
    UIManager(Player* p, World* w)
        : player(p), world(w),
          playerPanel(p),
          inventoryPanel(p),
          logPanel(w),
          menuPanel() {}

    void update() {
        inventoryPanel.update();
        menuPanel.update();
    }

    void render() {
        playerPanel.render();
        inventoryPanel.render();
        logPanel.render();
        menuPanel.render();
    }
};
