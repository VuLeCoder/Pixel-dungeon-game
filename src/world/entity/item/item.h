#pragma once
#include "../entity.h"
#include "item_type.h"

class ItemInstance;
class World;
class Player;

class Item : public Entity {
private:
    ItemInstance* instance;

public:
    Item(float x, float y, World* world, const ItemType& type);
    void update(float dt) override;
    void render() override;

    ItemInstance* getItemInstance() const { return instance; }

    void fall() override;
    bool isBlocking() const override;
    void takeDamage(int damage) override;

    void add();
    void use();
    void unequip();
};
