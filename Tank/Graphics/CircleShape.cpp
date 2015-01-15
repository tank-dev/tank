// Copyright (©) Jamie Bayne, David Truby, David Watson 2013-2014.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt)

#include "CircleShape.hpp"
#include "../System/Game.hpp"

namespace tank
{

CircleShape::CircleShape(float radius) : shape_(radius)
{
}
void CircleShape::setOpacity(uint8_t a)
{
    setFillOpacity(a);
    setOutlineOpacity(a);
}

void CircleShape::setFillOpacity(uint8_t a)
{
    auto fill = shape_.getFillColor();
    fill.a = a;
    shape_.setFillColor(fill);
}

void CircleShape::setOutlineOpacity(uint8_t a)
{
    auto outline = shape_.getOutlineColor();
    outline.a = a;
    shape_.setOutlineColor(outline);
}

Vectorf CircleShape::getSize() const
{
    auto rect = shape_.getGlobalBounds();
    return {rect.width, rect.height};
}

void CircleShape::draw(Transform const& parent, Camera const& cam)
{
    Graphic::transform(this, parent.position, parent.rotation, parent.origin,
                       cam, shape_);
    Game::window()->SFMLWindow().draw(shape_);
}
}
