#include "inventory_system.h"
#include "./../../entity/item/item.h"
#include "./../../entity/creature/player.h"
#include "./../../entity/item/item_instance.h"
#include "./../../world.h"
#include "./../../Level/level.h"

#include <iostream>

const std::vector<Item*>& InventorySystem::getInventory() const {
    return inventoryItems;
}

const std::vector<Item*>& InventorySystem::getEquipedItem() const {
    return equipItems;
}

bool InventorySystem::add(Item* item) {
    if(!item) return false;

    if(item->getItemInstance()->type.stackable) {
        for(auto& it : inventoryItems) {
            if(it->getItemInstance()->type.name == item->getItemInstance()->type.name) {
                it->add();
                item->getWorld()->getCurrLevel()->removeItemLevel(item);
                return true;
            }
        }
    }

    if((int)inventoryItems.size() >= capacity) return false;
    inventoryItems.push_back(item);
    item->getWorld()->getCurrLevel()->removeItemLevel(item);
    return true;
}
