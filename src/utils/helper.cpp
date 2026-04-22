#include "helper.h"
#include <cmath>
#include <algorithm>
const int TILE_SIZE = 16;

int distance(const Vector2& pos1, const Vector2& pos2) {
    int dx = std::abs((int)(pos1.x / TILE_SIZE) - (int)(pos2.x / TILE_SIZE));
    int dy = std::abs((int)(pos1.y / TILE_SIZE) - (int)(pos2.y / TILE_SIZE));
    return std::max(dx, dy);
}