#include "creature.h"
#include "../../world.h"

// public:
bool Creature::tryMove(int dx, int dy) {
    Vector2 pos = getPosition();
    targetPos = {
        pos.x + TILE_SIZE * dx,
        pos.y + TILE_SIZE * dy
    };
    int nx = targetPos.x / TILE_SIZE;
    int ny = targetPos.y / TILE_SIZE;

    Entity* target = getWorld()->getEntityAtTile(nx, ny);
    if(target) {
        if(target->isBlocking()) {
            attack(target);
            targetPos = pos;
            
            if (dx > 0) dir = Direction::RIGHT;
            else if (dx < 0) dir = Direction::LEFT;
            return false;
        }
    }

    if(!getWorld()->isPassable(nx, ny)) return false;
    
    setState(ActionState::MOVING);
    getWorld()->onLeft(pos.x / TILE_SIZE, pos.y / TILE_SIZE);
    getWorld()->onEnter(this, nx, ny);

    if (dx > 0) dir = Direction::RIGHT;
    else if (dx < 0) dir = Direction::LEFT;
    return true;
}

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

void Creature::update(float dt) {
    switch(state) {
        case ActionState::IDLE:
            setAnimation(AnimType::IDLE);
            break;

        case ActionState::MOVING:
        {
            setAnimation(AnimType::WALK);

            if(targetPos.x > pos.x) {
                pos.x += SPEED * dt;
                if(pos.x > targetPos.x) pos.x = targetPos.x;
            } else if(targetPos.x < pos.x) {
                pos.x -= SPEED  * dt;
                if(pos.x < targetPos.x) pos.x = targetPos.x;
            }

            if(targetPos.y > pos.y) {
                pos.y += SPEED * dt;
                if(pos.y > targetPos.y) pos.y = targetPos.y;
            } else if(targetPos.y < pos.y) {
                pos.y -= SPEED * dt;
                if(pos.y < targetPos.y) pos.y = targetPos.y;
            }

            if(pos.x == targetPos.x && pos.y == targetPos.y) {
                state = ActionState::IDLE;
            }

            break;
        }

        default:
            break;
    }
    currAnim->update(dt);
}

void Creature::render() {
    bool flip = dir == Direction::LEFT;
    currAnim->render(pos.x, pos.y, flip);
}
