#pragma once
#include <vector>

class Item;
class Player;

class InventorySystem {
private:
    static constexpr int equipCapacity = 3;
    static constexpr int capacity = 15;

    std::vector<Item*> equipItems;
    std::vector<Item*> items;

public:
    InventorySystem() {
        items.clear();
        equipItems.clear();
    }

    const std::vector<Item*>& getInventory() const;
    const std::vector<Item*>& getEquipedItem() const;

    bool add(Item* item);
    // void remove(int index);
    // void use(int index);
    // Item* get(int index);
    // int size() const;
};