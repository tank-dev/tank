// Copyright (©) Jamie Bayne, David Truby, David Watson 2013-2014.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt)

#include "Image.hpp"

#include <cmath>
#include <SFML/Graphics/RenderWindow.hpp>
#include "../System/Game.hpp"

namespace tank {

Image::Image(std::string file)
    : Image()
{
    load(file);
}

void Image::load(std::string file)
{
    if (not loaded_)
    {
        texture_.reset(new Texture());
        texture_->loadFromFile(file);
        sprite_.setTexture(*texture_);
    }
}

void Image::draw(Vectorf parentPos,
                 float parentRot,
                 Vectorf parentOri,
                 Camera const& cam)
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


    Graphic::transform(this, parentPos,parentRot, parentOri, cam, sprite_);
    Game::window()->SFMLWindow().draw(sprite_);

    //setScale(modelScale);
    //sprite_.setScale({modelScale.x, modelScale.y});
}

void Image::setSize(Vectorf size)
{
    sprite_.setScale(static_cast<float>(size.x/getClip().w),
                     static_cast<float>(size.y/getClip().h));
}

void Image::setClip(Vectoru dimensions, unsigned int index, Rectu clip)
{
    // TODO: This needs testing with rectangular dimensions
    Rectu new_clip = { 0, 0, dimensions.x, dimensions.y };

    const auto textureSize = getTextureSize();
    Vectoru usefulSize = {textureSize.x - (textureSize.x % dimensions.x),
                          textureSize.y - (textureSize.y % dimensions.y)};

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

}
