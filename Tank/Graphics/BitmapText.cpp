#include "BitmapText.hpp"

#include  <cmath>
#include  <iostream>

namespace tank
{

BitmapText::BitmapText(Image const& font, Vectoru glyphDimensions,
                       char asciiOffset, unsigned int rowWidth)
    : font_(font)
    , glyphDims_(glyphDimensions)
    , asciiOffset_(asciiOffset)
    , rowWidth_(rowWidth)
    , clip_({0, 0, glyphDims_.x, glyphDims_.y})
{
}

void BitmapText::setSize(Vectorf size)
{
    font_.setSize(size);
}
Vectorf BitmapText::getSize() const
{
    return font_.getSize();
}

void BitmapText::draw(Vectorf parentPos, float parentRot, Vectorf camera)
{
    Vectorf pos = getPos();
    float rot = getRotation();
    if(isRelativeToParent())
    {
        pos += parentPos;
        rot += parentRot;
    }

    for (unsigned int stringIndex = 0; text_[stringIndex] != '\0'; ++stringIndex)
    {
        unsigned int clipIndex = static_cast<unsigned int>(text_[stringIndex]
                                                           - asciiOffset_);
        clip_.x = (clipIndex % rowWidth_) * glyphDims_.x;
        clip_.y = (clipIndex / rowWidth_) * glyphDims_.y;

        font_.setClip(clip_);
        font_.setPos({ static_cast<float>(stringIndex * glyphDims_.x), 0 });

        font_.draw(pos, rot, camera);
    }
}

}
