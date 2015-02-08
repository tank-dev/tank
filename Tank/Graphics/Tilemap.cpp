// Copyright (©) Jamie Bayne, David Truby, David Watson 2013-2014.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt)

#include "Tilemap.hpp"
#include <cmath>

namespace tank
{

Tilemap::Tilemap(std::string file, Vector<unsigned> gridDims,
                 Vector<unsigned int> frameDims)
    : Image(file)
    , frameDimensions_(frameDims)
    , clipRect_{0, 0, frameDims.x, frameDims.y}
    , tiles_(gridDims)
{
    Image::setClip({0, 0, frameDims.x, frameDims.y});
}

void Tilemap::draw(Transform const& parent, Camera const& cam)
{
    auto originalPos = getPos();
    Vectorf dims = getTileDimensions();

    // Go through all of the tiles
    for (unsigned i = 0; i < tiles_.getWidth(); ++i) {
        for (unsigned j = 0; j < tiles_.getHeight(); ++j) {
            // Select the tile to draw
            Image::setClipByIndex(frameDimensions_, tiles_[Vectoru{i, j}], {},
                                  clipRect_);
            // Move to the correct place to draw the tile
            setPos(originalPos + Vectoru{i * dims.x, j * dims.y});
            // Draw the tile
            Image::draw(parent, cam);
        }
    }
    // Move back to the origin
    setPos(originalPos);
}

Vectoru Tilemap::getTile(const Vectorf& localCoords)
{
    Vectoru dims = getTileDimensions();
    return {std::floor(localCoords.x / dims.x),
            std::floor(localCoords.y / dims.y)};
}
}
