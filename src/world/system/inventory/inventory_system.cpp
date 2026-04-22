#include "inventory_system.h"
#include "./../../entity/item/item.h"
#include "./../../entity/creature/player.h"
#include "./../../entity/item/item_instance.h"
#include "./../../world.h"
#include "./../../Level/level.h"

#include <iostream>

const std::vector<Item*>& InventorySystem::getInventory() const {
    return items;
}

const std::vector<Item*>& InventorySystem::getEquipedItem() const {
    return equipItems;
}

bool InventorySystem::add(Item* item) {
    if(!item) return false;

    if(item->getItemInstance()->type.stackable) {
        for(auto& it : items) {
            if(it->getItemInstance()->type.name == item->getItemInstance()->type.name) {
                it->add();
                item->getWorld()->getCurrLevel()->removeItemLevel(item);
                return true;
            }
        }
    }

    if((int)items.size() > capacity) return false;

    std::cout << "Nhat nngol luon 1" <<std::endl;
    items.push_back(item);
    std::cout << "Nhat nngol luon 2" <<std::endl;
    item->getWorld()->getCurrLevel()->removeItemLevel(item);
    std::cout << "Nhat nngol luon 3" <<std::endl;
    return true;
}
