// Copyright (©) Jamie Bayne, David Truby, David Watson 2013-2014.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt)

#include "Image.hpp"

#include <cmath>
#include <SFML/Graphics/RenderWindow.hpp>
#include "../System/Game.hpp"

namespace tank {

Image::Image(std::string file) : Image()
{
    load(file);
}

void Image::load(std::string file)
{
    if (not loaded_) {
        texture_.reset(new Texture());
        texture_->loadFromFile(file);
        sprite_.setTexture(*texture_);
        pixels_.reset(new sf::Image(texture_->copyToImage()));
    }
}

void Image::draw(Transform const& t)
{
    /*
    /// Model ///
    const auto modelScale = getScale();
    auto modelPos = getPos();
    auto modelRot = getRotation();
    if(isRelativeToParent())
    {
        modelPos += parentPos;
        modelRot += parentRot;
    }

    /// View ///
    const auto viewScale = cam.getZoom();
    const auto viewRot = cam.getRotation();
    auto viewPos = cam.getPos();
    viewPos.x *= viewScale.x;
    viewPos.y *= viewScale.y;

    // Move to origin
    modelPos -= cam.getOrigin();

    Vectorf modelViewPos;
    // Rotate
    modelViewPos = modelPos.rotate(viewRot);
    // Scale
    modelViewPos.x *= viewScale.x;
    modelViewPos.y *= viewScale.y;
    // Translate
    modelViewPos -= viewPos.rotate(viewRot);

    // Move from origin
    modelViewPos += cam.getOrigin();

    float modelViewRot = modelRot + viewRot;

    //setScale({modelScale.x*viewScale.x, modelScale.y * viewScale.y});
    sprite_.setScale({modelScale.x*viewScale.x, modelScale.y * viewScale.y});

    /// Change sprite settings ///
    sprite_.setPosition({modelViewPos.x, modelViewPos.y});
    sprite_.setRotation(modelViewRot);
    */

    t.transform(sprite_);
    Game::window()->SFMLWindow().draw(sprite_);

    // setScale(modelScale);
    // sprite_.setScale({modelScale.x, modelScale.y});
}

void Image::setSize(Vectorf size)
{
    setScale({static_cast<float>(size.x/getClip().w),
            static_cast<float>(size.y/getClip().h)});
}

/*
void Image::setClip(Vectoru dimensions, unsigned int index)
{
    // TODO: This needs testing with rectangular dimensions
    Rectu clip = { 0, 0, dimensions.x, dimensions.y };

    const auto textureSize = getTextureSize();
    Vectoru usefulSize = {textureSize.x - (textureSize.x % dimensions.x),
                          textureSize.y - (textureSize.y % dimensions.y)};

    clip.x = (dimensions.x * index) % usefulSize.x;
    clip.y = dimensions.y * ((dimensions.x * index) / usefulSize.x);

    setClip(clip);
}
*/

void Image::setClipByIndex(Vectoru dimensions, unsigned int index,
                    Vectoru spacing, Rectu subClip)
{
    // TODO: This needs testing with rectangular dimensions
    Rectu newClip = {0, 0, dimensions.x, dimensions.y};

    auto textureSize = getTextureSize();

    // It is highly likly that subClip and textureSize are equal at least in
    // one coordinate
    if (subClip.x > textureSize.x or subClip.y > textureSize.y) {
        std::stringstream s;
        s << "subClip: (" << subClip.x << "," << subClip.y << "); textureSize: (" << textureSize.x << "," << textureSize.y << ")";
        throw std::invalid_argument("subClip bounds outside texture in setClipByIndex\n" + s.str());
    }

    textureSize -= Vectoru{subClip.x, subClip.y};

    const auto tileDimensions = dimensions + spacing;

    const Vectoru extraSpace = { textureSize.x % tileDimensions.x,
                                 textureSize.y % tileDimensions.y};

    const Vectoru usefulSize = { textureSize.x - extraSpace.x,
                                 textureSize.y - extraSpace.y };

    const unsigned widthInTiles = (usefulSize.x / tileDimensions.x)
                                  + extraSpace.x / dimensions.x;

    Vectoru tileCoords = { index % widthInTiles, index / widthInTiles };

    newClip.x = tileDimensions.x * tileCoords.x;
    newClip.y = tileDimensions.y * tileCoords.y;

    newClip.x += subClip.x;
    newClip.y += subClip.y;

    if (subClip.w != 0) {
        newClip.w = subClip.w;
    }
    if (subClip.h != 0) {
        newClip.h = subClip.h;
    }

    setClip(newClip);
}

void Image::makeUnique()
{
    pixels_.reset(new sf::Image(*pixels_));
    texture_.reset(new Texture(*texture_));
}

Color Image::getPixel(Vectoru coords)
{
    return pixels_->getPixel(coords.x, coords.y);
}

void Image::setPixel(Vectoru coords, Color c)
{
    pixels_->setPixel(coords.x, coords.y, c);
    texture_->update(*pixels_);
}

void Image::fillColor(Color target, Color fill)
{
    const sf::Vector2u size = pixels_->getSize();

    for (unsigned j = 0; j < size.y; ++j) {
        for (unsigned i = 0; i < size.x; ++i) {
            if (pixels_->getPixel(i, j) == target) {
                pixels_->setPixel(i, j, fill);
            }

        }
    }

    texture_->update(*pixels_);
}

void Image::setColorAlpha(Color target, uint8_t alpha)
{
    pixels_->createMaskFromColor(target, alpha);
    texture_->update(*pixels_);
}

}
