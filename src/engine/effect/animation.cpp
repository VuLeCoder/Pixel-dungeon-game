#include "animation.h"

void Animation::add(const FrameImage& frame, float delay) {
    frameImages.push_back(frame);
    delayFrames.push_back(delay);
    ignoreFrames.push_back(false);
}

void Animation::update(float time) {
    if(frameImages.empty()) return;

    timer += time;
    if(timer >= delayFrames[currFrame]) {
        nextFrame();
        timer = 0;
    }
}

void Animation::nextFrame() {
    if(currFrame >= frameImages.size() - 1) {
        if(isRepeated) currFrame = 0;
        else {
            finished = true;
            return;
        }
    } else {
        ++currFrame;
    }

    if(ignoreFrames[currFrame]) {
        if(currFrame < frameImages.size() - 1) nextFrame();
        else --currFrame;
    }
}

FrameImage& Animation::getCurrentFrame() {
    return frameImages[currFrame];
}

bool Animation::isLastFrame() const {
    return currFrame == frameImages.size() - 1;
}

bool Animation::isFinished() const {
    return finished;
}

void Animation::reset() {
    finished = false;
    currFrame = 0;
    timer = 0;
}

void Animation::setRepeated(bool repeat) {
    isRepeated = repeat;
}

void Animation::setIgnoreFrame(int id, bool val) {
    if(id >= 0 && id < ignoreFrames.size())
        ignoreFrames[id] = val;
}

void Animation::render(float x, float y, bool flip) {
    Texture2D texture = getCurrentFrame().getTexture();

    Rectangle src = getCurrentFrame().getSource();
    Rectangle dest = { x, y, src.width, src.height };

    if (flip) {
        src.width = -src.width;
    }

    DrawTexturePro(texture, src, dest, {0, 0}, 0.0f, WHITE);
}
