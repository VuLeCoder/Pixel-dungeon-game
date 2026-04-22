#pragma once

#include "../entity.h"
#include "item_type.h"

class Item : public Entity {
protected:
    Texture2D itemPng;

public:
    Item(float x, float y, World* world) : Entity(x, y, world) {}
    
    void fall() override;
    void update(float dt) override;
    void render() override;
};
