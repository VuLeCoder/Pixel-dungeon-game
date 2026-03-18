#pragma once

enum class DoorState {
    HIDDEN,
    CLOSED,
    LOCKED,
    OPEN
};

class Door {
private:
    DoorState state;

public:
    Door(bool locked = false, bool hidden = false) {
        if(hidden) state = DoorState::HIDDEN;
        else if(locked) state = DoorState::LOCKED;
        else state = DoorState::CLOSED;
    }
    
    bool isPassable() const {
        return state == DoorState::OPEN ||
                state == DoorState::CLOSED;
    }

    bool isBlockVision() const {
        return state != DoorState::OPEN;
    }

    bool isHidden() const {
        return state == DoorState::HIDDEN;
    }

    bool isLocked() const {
        return state == DoorState::LOCKED;
    }
    
    void reveal() {
        if(state == DoorState::HIDDEN) {
            state = DoorState::CLOSED;
        }
    }

    void unlock() {
        state = DoorState::CLOSED;
    }

    void open() {
        state = DoorState::OPEN;
    }

    void close() {
        state = DoorState::CLOSED;
    }
};