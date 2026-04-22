#include "inventory_system.h"
#include "./../../entity/item/item.h"
#include "./../../entity/creature/player.h"
#include "./../../entity/item/item_instance.h"
#include "./../../world.h"
#include "./../../Level/level.h"

#include <iostream>

InventorySystem::InventorySystem() {
    inventoryItems.clear();
    equipItems.clear();

    equipItems.reserve(3);
    equipItems[0] = nullptr;
    equipItems[1] = nullptr;
    equipItems[2] = nullptr;
}

const std::vector<Item*>& InventorySystem::getInventory() const {
    return inventoryItems;
}

const std::vector<Item*>& InventorySystem::getEquipedItem() const {
    return equipItems;
}

bool InventorySystem::add(Item* item) {
    if(!item) return false;

    if(item->getItemInstance()->type.category == ItemCategory::KEY) {
        Player* p = item->getWorld()->getPlayer();
        if(!p) return false;
        p->addKey();
        item->getWorld()->getCurrLevel()->removeItemLevel(item);
        return true;
    }

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

void InventorySystem::remove(Item* item) {
    if (!item) return;

    for(size_t i = 0; i < inventoryItems.size(); ++i) {
        if (inventoryItems[i] == item) {
            std::swap(inventoryItems[i], inventoryItems.back());

            inventoryItems.pop_back();
            return;
        }
    }
}

void InventorySystem::equip(Item *item) {
    if(!item) return;
    remove(item);
    
    switch(item->getItemInstance()->type.category) {
    case ItemCategory::WEAPON:
        equipItems[0] = item;
        break;
    case ItemCategory::ARMOR:
        equipItems[1] = item;
        break;
    case ItemCategory::RING:
        equipItems[2] = item;
        break;
    default:
        break;
    }
}

void InventorySystem::drop(Item* item) {
    remove(item);
    // item->getWorld()->getCurrLevel()->add
}

void InventorySystem::unequip(Item* item) {

}
