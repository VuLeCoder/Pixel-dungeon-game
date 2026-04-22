#include "idle_scene.h"
#include "../engine/asset_manager.h"
#include "../engine/scene_manager.h"
#include <cmath>

//public:
IdleScene::IdleScene() {
    idleTexture = AssetManager::GetTexture(AssetManager::IDLE_SCENE);
}

void IdleScene::update(float dt) {
    switch(state) {
        case State::FADE_IN:
            alpha -= speed * dt;
            if(alpha <= 0.0f) {
                alpha = 0.0f;
                state = State::WAIT;
            }
            break;

        case State::WAIT:
            waitTimer += dt;
            if(waitTimer >= waitDuration) {
                state = State::FADE_OUT;
            }
            break;

        case State::FADE_OUT:
            alpha += speed * dt;
            if(alpha >= 1.0f) {
                alpha = 1.0f;
                state = State::DONE;
            }
            break;

        case State::DONE:
            break;
    }
}

void IdleScene::render() {
    ClearBackground(BLACK);

    Vector2 pos = {
        (GetScreenWidth() - idleTexture.width * scale) / 2,
        (GetScreenHeight() - idleTexture.height * scale) / 2
    };

    DrawTextureEx(idleTexture, pos, 0.0f, scale, WHITE);

    float pulse = (sinf(GetTime() * 3) + 1) / 2;
    Color textColor = Fade(WHITE, pulse);

    DrawText("Đang đi đến tầng...", pos.x, pos.y + idleTexture.height * scale + 20, 30, textColor);

    DrawRectangle(
        0, 0,
        GetScreenWidth(),
        GetScreenHeight(),
        Fade(BLACK, alpha)
    );
}

void IdleScene::resetScnene() {
    alpha = 1.0f;
    state = State::FADE_IN;
    waitTimer = 0.0f;
}

bool IdleScene::isEndIdle() const {
    return state == State::DONE;
}
