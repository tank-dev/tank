// Copyright (©) Jamie Bayne, David Truby, David Watson 2013-2014.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt)

#include "RectangleShape.hpp"

#include "../System/Game.hpp"
#include "Shader.hpp"

namespace tank {

RectangleShape::RectangleShape(Vectorf size)
    : rectangleShape_({size.x, size.y})
{
}

RectangleShape::RectangleShape(Rectf rect)
    : rectangleShape_({rect.w, rect.h})
{
    setPos({rect.x,rect.y});
}

void RectangleShape::setFillColor(Color c)
{
    rectangleShape_.setFillColor(c);
}
void RectangleShape::setOutlineColor(Color c)
{
    rectangleShape_.setOutlineColor(c);
}
void RectangleShape::setOutlineThickness(float thickness)
{
    rectangleShape_.setOutlineThickness(thickness);
}
Color const& RectangleShape::getFillColor() const
{
    return rectangleShape_.getFillColor();
}
Color const& RectangleShape::getOutlineColor() const
{
    return rectangleShape_.getOutlineColor();
}
float RectangleShape::getOutlineThickness() const
{
    return rectangleShape_.getOutlineThickness();
}

void RectangleShape::setSize(Vectorf size)
{
    rectangleShape_.setSize({size.x, size.y});
}

Vectorf RectangleShape::getSize() const
{
    auto rect = rectangleShape_.getGlobalBounds();
    return {rect.width, rect.height};
}

void RectangleShape::draw(Vectorf parentPos,
                          float parentRot,
                          Vectorf parentOri,
                          Camera const& cam)
{
    Graphic::transform(this, parentPos, parentRot, parentOri,
                       cam, rectangleShape_);
    Game::window()->SFMLWindow().draw(rectangleShape_, getShader().get());
}


}
