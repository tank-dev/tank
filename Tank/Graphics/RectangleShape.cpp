// Copyright (©) Jamie Bayne, David Truby, David Watson 2013-2014.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt)

#include "RectangleShape.hpp"
#include "../System/Game.hpp"

namespace tank {

RectangleShape::RectangleShape(Vectorf size)
    : shape_({size.x, size.y})
{
}

void RectangleShape::setOpacity(uint8_t a)
{
    setFillOpacity(a);
    setOutlineOpacity(a);
}

void RectangleShape::setFillOpacity(uint8_t a)
{
    auto fill = shape_.getFillColor();
    fill.a = a;
    shape_.setFillColor(fill);
}

void RectangleShape::setOutlineOpacity(uint8_t a)
{
    auto outline = shape_.getOutlineColor();
    outline.a = a;
    shape_.setOutlineColor(outline);
}

RectangleShape::RectangleShape(Rectf rect)
    : shape_({rect.w, rect.h})
{
    setPos({rect.x,rect.y});
}
void RectangleShape::setSize(Vectorf size)
{
    shape_.setSize({size.x, size.y});
}

Vectorf RectangleShape::getSize() const
{
    auto rect = shape_.getGlobalBounds();
    return {rect.width, rect.height};
}

void RectangleShape::draw(Transform const& parent, Camera const& cam)
{
    Graphic::transform(this, parent.position, parent.rotation, parent.origin,
                       cam, shape_);
    Game::window()->SFMLWindow().draw(shape_);
}

}
