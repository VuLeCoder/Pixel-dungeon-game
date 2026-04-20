#include "fov_system.h"
#include "../../level/level.h"

//private:
void FOVSystem::castLight(
    Level* level,
    int cx, int cy,
    int row,
    float startSlope,
    float endSlope,
    int radius,
    int xx, int xy, int yx, int yy,
    std::vector<std::vector<bool>>& visible
) {
    if(startSlope < endSlope) return;
    int size = Level::MAP_SIZE;

    for(int i=row; i<=radius; ++i) {
        bool blocked = false;
        float newStart = startSlope;

        for(int dx=-i, dy=-i; dx<=0; ++dx) {
            float lSlope = (dx - 0.5f) / (dy + 0.5f);
            float rSlope = (dx + 0.5f) / (dy - 0.5f);

            if (rSlope > startSlope) continue;
            if (lSlope < endSlope) break;

            int sax = dx * xx + dy * xy;
            int say = dx * yx + dy * yy;

            int ax = cx + sax;
            int ay = cy + say;

            if(ax < 0 || ay < 0 || ax >= size || ay >= size) continue;

            if(std::max(std::abs(dx), std::abs(dy)) <= radius) {
                visible[ax][ay] = true;
            }

            bool isWall = level->isBlockVision(ax, ay);
            if(blocked) {
                if(isWall) {
                    newStart = rSlope;
                } else {
                    blocked = false;
                    startSlope = newStart;
                }
            } else {
                if(isWall && i < radius) {
                    blocked = true;

                    castLight(level, cx, cy, i + 1,
                              startSlope, lSlope,
                              radius,
                              xx, xy, yx, yy,
                              visible);

                    newStart = rSlope;
                }
            }
        }

        if (blocked) break;
    }
}

//public:
FOVSystem::Result FOVSystem::compute(
    Level* level,
    int cx, int cy,
    int radius
) {
    int size = Level::MAP_SIZE;

    Result result;
    result.visible = std::vector<std::vector<bool>>(
        size, std::vector<bool>(size, false)
    );

    computeInto(level, cx, cy, radius, result.visible);
    return result;
}

void FOVSystem::computeInto(
    Level* level,
    int cx, int cy,
    int radius,
    std::vector<std::vector<bool>>& visible
) {
    int size = Level::MAP_SIZE;

    for(int x=0; x<size; ++x) {
        for(int y=0; y<size; ++y) {
            visible[x][y] = false;
        }
    }

    visible[cx][cy] = true;

    int multipliers[8][4] = {
        {1, 0, 0, 1}, {0, 1, 1, 0},
        {-1, 0, 0, 1}, {0, -1, 1, 0},
        {-1, 0, 0, -1}, {0, -1, -1, 0},
        {1, 0, 0, -1}, {0, 1, -1, 0}
    };

    for(int i=0; i<8; ++i) {
        castLight(level, cx, cy, 1, 1.0f, 0.0f, radius,
                  multipliers[i][0], multipliers[i][1],
                  multipliers[i][2], multipliers[i][3],
                  visible);
    }
}

