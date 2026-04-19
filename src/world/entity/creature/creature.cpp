#include "creature.h"

void Creature::takeDamage(int damage) {
    hp -= damage;
    if(hp <= 0) destroy();
}

void Creature::setAnimation(AnimType type) {
    Animation* next = &anims[static_cast<int>(type)];

    if(currAnim != next) {
        currAnim = next;
        currAnim->reset();
    }
}

void Creature::render() {
    bool flip = dir == Direction::LEFT;
    currAnim->render(pos.x, pos.y, flip);
}
