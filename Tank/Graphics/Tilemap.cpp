// Copyright (©) Jamie Bayne, David Truby, David Watson 2013-2014.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt)

#include "Tilemap.hpp"

#include <algorithm>
#include <stdexcept>

namespace tank
{

Tilemap::Tilemap(Image const& img,
                 Vector<unsigned> gridDims,
                 Vector<unsigned int> frameDims)
        : image_(img)
        , frameDimensions_(frameDims)
        , tiles_(gridDims)
{
}

void Tilemap::draw(Transform const& t)
{
    Vectorf dims = getTileDimensions();

    Transform localPositioning;
    localPositioning.setScale(t.getScale());

    // Go through all of the tiles
    for (unsigned i = 0; i < tiles_.getWidth(); ++i) {
        for (unsigned j = 0; j < tiles_.getHeight(); ++j) {
            // Select the tile to draw
            image_.setClipByIndex(frameDimensions_, 
                                  tiles_[Vectoru{i, j}],
                                  {}, 
                                  clipRect_);
            // Move to the correct place to draw the tile
            localPositioning.setOffset(Vectoru{i * dims.x, j*dims.y});
            // Draw the tile
            image_.draw(t(localPositioning));
        }
    }
}

void Tilemap::setImage(Image const& image,
                         Vectoru frameDims,
                         Vectoru spacing,
                         Rectu subClip)
{
    image_ = image;
    frameDimensions_ = frameDims;
    //spacing_ = spacing;
    clipRect_ = subClip;
}

/*
void Tilemap::setClipByIndex(Vectoru dimensions, unsigned int index,
                             Vectoru spacing, Rectu clip)
{
    // TODO: This needs testing with rectangular dimensions
    Rectu new_clip = {0, 0, dimensions.x, dimensions.y};

    Vectoru usefulSize = {
            frameDimensions_.x - (frameDimensions_.x % dimensions.x),
            frameDimensions_.y - (frameDimensions_.y % dimensions.y)};

    new_clip.x = (dimensions.x * index) % usefulSize.x;
    new_clip.y = dimensions.y * ((dimensions.x * index) / usefulSize.x);

    if (clip != Rectu{0, 0, 0, 0}) {
        new_clip.x += clip.x;
        new_clip.y += clip.y;
        new_clip.w = clip.w;
        new_clip.h = clip.h;
    }

    setClip(clip);
}
*/

Vectoru Tilemap::getTile(const Vectorf& localCoords)
{
    Vectoru dims = getTileDimensions();
    return {std::floor(localCoords.x / dims.x),
            std::floor(localCoords.y / dims.y)};
}
}
