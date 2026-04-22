#pragma once
#include "raylib.h"

class IdleScene {
private:
    Texture2D idleTexture;

    static constexpr float scale = 2.1375f;

    float alpha = 1.0f;
    float speed = 1.5f;

    enum class State {
        FADE_IN,
        WAIT,
        FADE_OUT,
        DONE
    };

    State state = State::FADE_IN;
    float waitTimer = 0.0f;
    float waitDuration = 0.8f;
public:
    IdleScene();
    void update(float dt);
    void render();

    void resetScnene();
    bool isEndIdle() const; 
};
