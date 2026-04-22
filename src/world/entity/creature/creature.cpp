#include "creature.h"
#include "../../world.h"

//protected:
void Creature::updateUse() {
    endTurn();
}
void Creature::updateUseScroll() {
    endTurn();
}

void Creature::updateFast() {
    switch(state) {
        case ActionState::MOVING:
            pos = targetPos;
            setState(ActionState::IDLE);
            endTurn();
            break;

        case ActionState::ATTACKING:
            setState(ActionState::IDLE);
            endTurn();
            break;

        case ActionState::DEATH:
            Entity::destroy();
            endTurn();
            break;

        case ActionState::IDLE:
        default:
            endTurn();
            break;
    }
}

//private:
void Creature::updateMovement(float dt) {
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
        setState(ActionState::IDLE);
        endTurn();
    }
}

void Creature::updateAttack() {
    if(currAnim->isFinished()) {
        setState(ActionState::IDLE);
        endTurn();
    }
}

void Creature::updateDeath() {
    if(currAnim->isFinished()) {
        Entity::destroy();
        endTurn();
    }
}

// public:
void Creature::update(float dt) {
    if(!isPlayerSeen()) {
        updateFast();
        return;
    }

    switch(state) {
        case ActionState::IDLE:
            endTurn();
            break;

        case ActionState::MOVING:
            updateMovement(dt);
            break;

        case ActionState::ATTACKING:
            updateAttack();
            break;
        
        case ActionState::DEATH:
            updateDeath();
            break;

        default:
            break;
    }
    currAnim->update(dt);
}

void Creature::render() {
    if(!isPlayerSeen()) {
        return;
    }

    bool flip = dir == Direction::LEFT;
    currAnim->render(pos.x, pos.y, flip);
}


void Creature::setAnimation(AnimType type) {
    Animation* next = &anims[static_cast<int>(type)];

    if(currAnim != next) {
        currAnim = next;
        currAnim->reset();
    }
}

void Creature::setState(ActionState newState) {
    if(state == newState || state == ActionState::DEATH) return;
    state = newState;

    switch(state) {
        case ActionState::IDLE:
            setAnimation(AnimType::IDLE);
            break;
        case ActionState::MOVING:
            setAnimation(AnimType::WALK);
            break;
        case ActionState::ATTACKING:
            setAnimation(AnimType::ATK);
            break;
        case ActionState::USE:
            setAnimation(AnimType::USE);
            break;
        case ActionState::USE_SCROLL:
            setAnimation(AnimType::USE_SCROLL);
            break;
        case ActionState::DEATH:
            setAnimation(AnimType::DEATH);
            break;
    }
}


void Creature::destroy() {
    setState(ActionState::DEATH);
}

bool Creature::tryMove(int dx, int dy) {
    Vector2 pos = getPosition();
    Vector2 nextPos = {
        pos.x + TILE_SIZE * dx,
        pos.y + TILE_SIZE * dy
    };
    int nx = nextPos.x / TILE_SIZE;
    int ny = nextPos.y / TILE_SIZE;

    Entity* target = getWorld()->getEntityAtTile(nx, ny);
    if(target && target != this) {
        if(target->isBlocking()) {
            if(target->isPlayer() != isPlayer()) {
                attack(target);
            }
            
            if (dx > 0) dir = Direction::RIGHT;
            else if (dx < 0) dir = Direction::LEFT;
            return true;
        }
    }

    if(!getWorld()->isPassable(nx, ny)) {
        if(!getWorld()->isDoor(nx, ny)) return false;
        if(!isPlayer()) return false;

        Player* p = static_cast<Player*>(this);
        if(p->hasKey()) {
            p->useKey();
            getWorld()->onEnter(this, nx, ny);
            return true;
        }
        return false;
    }
    setTargetPos(nextPos.x, nextPos.y);
    
    setState(ActionState::MOVING);
    getWorld()->onLeft(pos.x / TILE_SIZE, pos.y / TILE_SIZE);
    getWorld()->onEnter(this, nx, ny);

    if (dx > 0) dir = Direction::RIGHT;
    else if (dx < 0) dir = Direction::LEFT;
    return true;
}

void Creature::takeDamage(int damage) {
    damage -= GetRandomValue(getStats().minDef, getStats().maxDef);
    damage = damage > 0 ? damage : 0;

    currHP -= damage;
    if(currHP <= 0) destroy();
}

void Creature::takeTurn(bool isPlayerSeen) {
    setPlayerSeen(isPlayerSeen);
    startTurn();
}


void Creature::heal(int hp) {
    currHP += hp; 
    currHP = currHP <= getStats().maxHP ? currHP : getStats().maxHP;
}

void Creature::addStats(Stats add) {
    Stats currStats = getStats();

    currStats.maxHP     += add.maxHP;
    currStats.minDame   += add.minDame;
    currStats.maxDame   += add.maxDame;
    currStats.minDef    += add.minDef;
    currStats.maxDef    += add.maxDef;

    currStats.visionRange += add.visionRange;

    setStats(currStats);
}

void Creature::removeStats(Stats remove) {
    Stats currStats = getStats();

    currStats.maxHP = (currStats.maxHP - remove.maxHP) > 0 ? (currStats.maxHP - remove.maxHP) : 0;

    currStats.minDame = (currStats.minDame - remove.minDame) > 0 ? (currStats.minDame - remove.minDame) : 0;
    currStats.maxDame = (currStats.maxDame - remove.maxDame) > 1 ? (currStats.maxDame - remove.maxDame) : 1;
    currStats.minDame = (currStats.minDame < currStats.maxDame) ? currStats.minDame : currStats.maxDame - 1;

    currStats.minDef  = (currStats.minDef - remove.minDef) > 0 ? (currStats.minDef - remove.minDef) : 0;
    currStats.maxDef  = (currStats.maxDef - remove.maxDef) > 0 ? (currStats.maxDef - remove.maxDef) : 0;
    currStats.minDef  = (currStats.minDef < currStats.maxDef) ? currStats.minDef : currStats.maxDef - 1;

    currStats.visionRange = (currStats.visionRange - remove.visionRange) > 0 ? (currStats.visionRange - remove.visionRange) : 0;
    setStats(currStats);
}
