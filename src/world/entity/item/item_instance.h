#pragma once
#include "raylib.h"
#include "item_type.h"

class ItemInstance {
private:
    Texture2D png;

    bool identified = true;

    int quantity = 1;
    int durability = 0;
    
public:
    const ItemType type;

    ItemInstance(const ItemType& type);

    const Texture2D& getTexture() const { return png; }
    
    int getQuantity() const { return quantity; }
    bool canUse() const { return quantity > 0; }
    void use() { --quantity; }
};
