#pragma once

#include "raylib.h"

class MyCamera {
private:
    Camera2D cam;

    float worldWidth;
    float worldHeight;

    float screenWidth;
    float screenHeight;

    float zoom;
    float minZoom;
    float maxZoom;

    bool isDragging = false;
    Vector2 lastMousePos;

    float padding = 500;

public:
    MyCamera(float screenW, float screenH, float worldW, float worldH);

    void setZoom(float value);
    void updateZoom(float delta);

    void follow(Vector2 target);
    void followSmooth(Vector2 target, float dt, float speed = 5.0f);
    void handleDrag();

    void applyClamp();

    void begin();
    void end();

    Vector2 worldToScreen(Vector2 worldPos) const;
    Vector2 screenToWorld(Vector2 screenPos) const;

    Camera2D& getRaw(); // nếu cần dùng trực tiếp raylib
};