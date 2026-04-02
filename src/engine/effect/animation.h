#pragma once
#include <vector>
#include <string>
#include "frame_image.h"

class Animation {
private:
    bool isRepeated = true;
    int currFrame = 0;

    std::vector<FrameImage> frameImages;
    std::vector<bool> ignoreFrames;
    std::vector<float> delayFrames;

    float timer = 0.0f;

public:
    Animation() {}

    void add(const FrameImage& frame, float delay);
    void update(float time);
    void nextFrame();

    FrameImage& getCurrentFrame();
    bool isLastFrame() const;

    void reset();
    void setRepeated(bool repeat);
    void setIgnoreFrame(int id, bool val);

    void render(float x, float y, bool flip);
};
