#include "frame_image.h"

const Texture2D& FrameImage::getTexture() const { 
    return texture;
}

Rectangle FrameImage::getSource() const {
    return source;
}

void FrameImage::setTexture(Texture2D tex) {
    texture = tex;
}
