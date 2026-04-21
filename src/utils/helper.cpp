#include "helper.h"
#include <cmath>
const int TILE_SIZE = 16;

int distance(const Vector2& pos1, const Vector2& pos2) {
    float dx = (pos1.x - pos2.x) / TILE_SIZE;
    float dy = (pos1.y - pos2.y) / TILE_SIZE;
    return static_cast<int>(std::sqrt(dx * dx + dy * dy));
}