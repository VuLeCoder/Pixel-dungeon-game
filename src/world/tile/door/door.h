#pragma once

#include "door_state.h"

class Door {
private:
    DoorState state;

public:
    Door(bool locked = false, bool hidden = false);
    DoorState getState() const;
    
    bool isPassable() const;
    bool isBlockVision() const;
    bool isHidden() const;
    bool isLocked() const;

    void reveal();
    void unlock();
    void open();
    void close();
};