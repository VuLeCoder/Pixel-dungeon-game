#pragma once

#include <vector>

class Level;

class FOVSystem {
public:
    struct Result {
        std::vector<std::vector<bool>> visible;
    };

    static Result compute(
        Level* level,
        int cx, int cy,
        int radius
    );

    static void computeInto(
        Level* level,
        int cx, int cy,
        int radius,
        std::vector<std::vector<bool>>& visible
    );

private:
    static void castLight(
        Level* level,
        int cx, int cy,
        int row,
        float startSlope,
        float endSlope,
        int radius,
        int xx, int xy, int yx, int yy,
        std::vector<std::vector<bool>>& visible
    );
};