/* This file is part of Tank.
 *
 * Tank is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Lesser General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * Tank is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License and
 * the GNU Lesser General Public Licence along with Tank. If not, see
 * <http://www.gnu.org/licenses/>.
 *
 * Copyright 2013 (©) Jamie Bayne, David Truby, David Watson.
 */

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

void BitmapText::draw(Vectorf parentPos, float parentRot, Camera const& cam)
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

        const float rads = 3.14159265 * rot / 180.f;
        const float distance = stringIndex * glyphDims_.x;
        Vectorf displacement;
        displacement.x = distance * std::cos(rads);
        displacement.y = distance * std::sin(rads);

        font_.setClip(clip_);
        font_.setPos(displacement);

        font_.draw(pos, rot, cam);
    }
}

}
