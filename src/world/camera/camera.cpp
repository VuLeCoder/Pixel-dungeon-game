#include "camera.h"
#include <algorithm>

MyCamera::MyCamera(float screenW, float screenH, float worldW, float worldH)
    : screenWidth(screenW), screenHeight(screenH),
      worldWidth(worldW), worldHeight(worldH)
{
    cam.target = {
        worldWidth / 2.0f,
        worldHeight / 2.0f
    };
    cam.offset = {screenW / 2.0f, screenH / 2.0f};
    cam.rotation = 0.0f;
    cam.zoom = 2.0f;

    minZoom = 2.0f;
    maxZoom = 5.0f;
}

void MyCamera::follow(Vector2 target) {
    cam.target = target;
    applyClamp();
}

void MyCamera::followSmooth(Vector2 target, float dt, float speed) {
    cam.target.x += (target.x - cam.target.x) * speed * dt;
    cam.target.y += (target.y - cam.target.y) * speed * dt;

    applyClamp();
}

void MyCamera::applyClamp() {
    float halfW = (screenWidth / 2.0f) / cam.zoom;
    float halfH = (screenHeight / 2.0f) / cam.zoom;

    float dynamicPadding = padding / cam.zoom;

    float minX = -dynamicPadding;
    float maxX = worldWidth + dynamicPadding;

    float minY = -dynamicPadding;
    float maxY = worldHeight + dynamicPadding;

    cam.target.x = std::clamp(
        cam.target.x,
        minX + halfW,
        maxX - halfW
    );

    cam.target.y = std::clamp(
        cam.target.y,
        minY + halfH,
        maxY - halfH
    );
}

void MyCamera::begin() {
    BeginMode2D(cam);
}

void MyCamera::end() {
    EndMode2D();
}

Vector2 MyCamera::worldToScreen(Vector2 worldPos) const {
    return GetWorldToScreen2D(worldPos, cam);
}

Vector2 MyCamera::screenToWorld(Vector2 screenPos) const {
    return GetScreenToWorld2D(screenPos, cam);
}

Camera2D& MyCamera::getRaw() {
    return cam;
}

void MyCamera::setZoom(float value) {
    zoom = std::clamp(value, minZoom, maxZoom);
    cam.zoom = zoom;
}

void MyCamera::updateZoom(float delta) {
    if (delta == 0) return;

    Vector2 mouseWorldBefore = GetScreenToWorld2D(GetMousePosition(), cam);

    zoom += delta;
    zoom = std::clamp(zoom, minZoom, maxZoom);
    cam.zoom = zoom;

    Vector2 mouseWorldAfter = GetScreenToWorld2D(GetMousePosition(), cam);

    cam.target.x += (mouseWorldBefore.x - mouseWorldAfter.x);
    cam.target.y += (mouseWorldBefore.y - mouseWorldAfter.y);

    applyClamp();
}

void MyCamera::handleDrag() {
    // bắt đầu drag
    if (IsMouseButtonPressed(MOUSE_RIGHT_BUTTON)) {
        isDragging = true;
        lastMousePos = GetMousePosition();
    }

    // đang drag
    if (IsMouseButtonDown(MOUSE_RIGHT_BUTTON) && isDragging) {
        Vector2 mousePos = GetMousePosition();

        Vector2 delta = {
            mousePos.x - lastMousePos.x,
            mousePos.y - lastMousePos.y
        };

        // 🔥 QUAN TRỌNG: chia cho zoom
        delta.x /= cam.zoom;
        delta.y /= cam.zoom;

        cam.target.x -= delta.x;
        cam.target.y -= delta.y;

        lastMousePos = mousePos;

        applyClamp();
    }

    // thả chuột
    if (IsMouseButtonReleased(MOUSE_RIGHT_BUTTON)) {
        isDragging = false;
    }
}
