#pragma once
#include "raylib.h"

class FrameImage {
private:
    Texture2D texture;
    Rectangle source;

public:
    FrameImage() {}
    FrameImage(Texture2D tex, Rectangle src)
        : texture(tex), source(src) {}

    const Texture2D& getTexture() const;
    Rectangle getSource() const;

    void setTexture(Texture2D tex);
};
