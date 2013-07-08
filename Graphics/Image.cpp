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

#include <SFML/Graphics/RenderWindow.hpp>
#include "../System/Game.hpp"

#include <iostream>

namespace tank {

Image::Image()
    : loaded_(false)
    , size_({0.f, 0.f})
    , texture_(nullptr)
{
}

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

void Image::draw(Vectorf parentPos, float parentRot, Vectorf camera)
{
    Vectorf pos = getPos() - camera;
    float angle = getRotation();

    if(isRelativeToParent())
    {
        pos += parentPos;
        angle += parentRot;
    }

    sprite_.setPosition({pos.x, pos.y});
    sprite_.setRotation(angle);


    Game::window()->SFMLWindow().draw(sprite_);
}

void Image::setSize(Vectorf size)
{
    size_ = size;

    std::cout << "Element's clip: " << getClip().w  << ", " << getClip().h
              << std::endl
              << "Same Element's tSize: " << getTextureSize().x << ", "
              << getTextureSize().y << std::endl;
    sprite_.setScale(static_cast<float>(size.x/getClip().w),
                     static_cast<float>(size.y/getClip().h));
}


}
