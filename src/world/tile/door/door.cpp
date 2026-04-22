#include "door.h"

Door::Door(bool locked, bool hidden) {
    if(hidden) state = DoorState::HIDDEN;
    else if(locked) state = DoorState::LOCKED;
    else state = DoorState::CLOSED;
}

DoorState Door::getState() const {
    return state;
}

bool Door::isPassable() const {
    return state == DoorState::OPEN ||
            state == DoorState::CLOSED;
}

bool Door::isBlockVision() const {
    return state != DoorState::OPEN;
}

bool Door::isHidden() const {
    return state == DoorState::HIDDEN;
}

bool Door::isLocked() const {
    return state == DoorState::LOCKED;
}

void Door::reveal() {
    if(state == DoorState::HIDDEN) {
        state = DoorState::CLOSED;
    }
}

void Door::unlock() {
    state = DoorState::CLOSED;
}

void Door::open() {
    state = DoorState::OPEN;
}

void Door::close() {
    state = DoorState::CLOSED;
}
