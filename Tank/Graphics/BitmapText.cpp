// Copyright (©) Jamie Bayne, David Truby, David Watson 2013-2014.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt)

#include "BitmapText.hpp"

#include <cmath>
#include <iostream>

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
    font_.setClip(clip_);
    font_.setParent(this);
    // font_.setSize(glyphDims_);
}

void BitmapText::setGlyphSize(Vectorf size)
{
    font_.setSize(size);
}
Vectorf BitmapText::getGlyphSize() const
{
    return font_.getSize();
}

Vectorf BitmapText::getSize() const
{
    int nChars = text_.size();

    auto size = getGlyphSize();
    size.x *= nChars;

    return size;
}

void BitmapText::draw()
{
    const float rot = getRotation();

    for (std::size_t stringIndex = 0; text_[stringIndex] != '\0';
         ++stringIndex) {
        auto clipIndex =
                static_cast<unsigned int>(text_[stringIndex] - asciiOffset_);
        clip_.x = (clipIndex % rowWidth_) * glyphDims_.x;
        clip_.y = (clipIndex / rowWidth_) * glyphDims_.y;

        const float rads = 3.14159265 * rot / 180.f;
        const float distance = stringIndex * glyphDims_.x;
        Vectorf displacement;
        displacement.x = distance * std::cos(rads);
        displacement.y = distance * std::sin(rads);

        font_.setClip(clip_);
        font_.setPos(displacement);

        font_.draw();
    }
}
}
