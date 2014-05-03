// Copyright (©) Jamie Bayne, David Truby, David Watson 2013-2014.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt)

#include "Tilemap.hpp"

#include <algorithm>

namespace tank
{

Tilemap::Tilemap(std::string file, Vector<unsigned> gridDims,
                 Vector<unsigned int> frameDims)
    : Image(file)
    , frameDimensions_(frameDims)
    , tiles_(gridDims)
{
    Image::setClip({0,0,frameDims.x, frameDims.y});
    //image_.setSize(frameDims);
}

void Tilemap::draw(Vectorf parentPos,
                     float parentRot,
                     Vectorf parentOri,
                     Camera const& cam)
{
    auto originalPos = getPos();
    Vectoru dims;
    // Get the dimensions of the draw area
    if (clipRect_ == Rectu{0,0,0,0}) 
    {
        dims = frameDimensions_;
    }
    else
    {
        dims = Vectoru{clipRect_.w, clipRect_.h};
    }

    // Go through all of the tiles
    for (unsigned i = 0; i < tiles_.getWidth(); ++i)
    {
        for (unsigned j = 0; j < tiles_.getHeight(); ++j)
        {
            // Select the tile to draw
            Image::setClip(frameDimensions_, tiles_[Vectoru{i,j}], clipRect_);
            // Move to the correct place to draw the tile
            setPos(originalPos + Vectoru{i * dims.x, j*dims.y});
            // Draw the tile
            Image::draw(parentPos, parentRot, parentOri, cam);
        }
    }
    // Move back to the origin
    setPos(originalPos);
}

void Tilemap::setClip(Vectoru dimensions, unsigned int index, Rectu clip)
{
    // TODO: This needs testing with rectangular dimensions
    Rectu new_clip = { 0, 0, dimensions.x, dimensions.y };

    Vectoru usefulSize = {frameDimensions_.x - (frameDimensions_.x % dimensions.x),
                          frameDimensions_.y - (frameDimensions_.y % dimensions.y)};

    new_clip.x = (dimensions.x * index) % usefulSize.x;
    new_clip.y = dimensions.y * ((dimensions.x * index) / usefulSize.x);

    if (clip != Rectu{0,0,0,0})
    {
        new_clip.x += clip.x;
        new_clip.y += clip.y;
        new_clip.w = clip.w;
        new_clip.h = clip.h;
    }

    setClip(clip);
}

void Tilemap::setLine(const Vectoru& start, const Vectoru& end, unsigned value)
{
    tiles_.setLine(start, end, value);
}

}
