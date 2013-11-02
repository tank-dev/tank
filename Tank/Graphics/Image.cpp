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
    if(not loaded_)
    {
        texture_.reset(new Texture());
        texture_->loadFromFile(file);
        sprite_.setTexture(*texture_);
    }
}

void Image::draw(Vectorf parentPos, float parentRot, Camera const& cam)
{
    const auto windowSize = Game::window()->getSize();
    /* Model */
    auto modelPos = getPos();
    auto modelRot = getRotation();
    if(isRelativeToParent())
    {
        modelPos += parentPos;
        modelRot += parentRot;
    }

    /* View */
    const auto viewRot = cam.getRotation();
    const float viewRads = 3.14159265 * viewRot / 180.f;

    modelPos -= cam.getOrigin();
    Vectorf modelViewPos;
    modelViewPos.x = modelPos.x * std::cos(viewRads) + modelPos.y * std::sin(viewRads);
    modelViewPos.y = - modelPos.x * std::sin(viewRads) + modelPos.y * std::cos(viewRads);
    modelViewPos += cam.getOrigin();
    modelViewPos -= cam.getPos();

    float modelViewRot = modelRot - viewRot;

    /* Change sprite settings */
    sprite_.setPosition({modelViewPos.x, modelViewPos.y});
    sprite_.setRotation(modelViewRot);


    Game::window()->SFMLWindow().draw(sprite_);
}

void Image::setSize(Vectorf size)
{
    sprite_.setScale(static_cast<float>(size.x/getClip().w),
                     static_cast<float>(size.y/getClip().h));
}

void Image::setClip(Vectoru dimensions, unsigned int index)
{
    // TODO: This needs testing with rectangular dimensions
    Rectu clip = { 0, 0, dimensions.x, dimensions.y };

    Vectoru usefulSize = { getTextureSize().x -
                                ( getTextureSize().x % dimensions.x ),
                           getTextureSize().y -
                                ( getTextureSize().y % dimensions.y )};

    clip.x = (dimensions.x * index) % usefulSize.x;
    clip.y = dimensions.y * ((dimensions.x * index) / usefulSize.x);

    setClip(clip);
}

}
