// Copyright (©) Jamie Bayne, David Truby, David Watson 2013-2014.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt)

#include "ConvexShape.hpp"
#include "../System/Game.hpp"

namespace tank
{

ConvexShape::ConvexShape(std::vector<Vectorf> const& points)
{
    setPoints(points);
}

void ConvexShape::setOpacity(uint8_t a)
{
    setFillOpacity(a);
    setOutlineOpacity(a);
}

void ConvexShape::setFillOpacity(uint8_t a)
{
    auto fill = shape_.getFillColor();
    fill.a = a;
    shape_.setFillColor(fill);
}

void ConvexShape::setOutlineOpacity(uint8_t a)
{
    auto outline = shape_.getOutlineColor();
    outline.a = a;
    shape_.setOutlineColor(outline);
}


Vectorf ConvexShape::getSize() const
{
    auto rect = shape_.getGlobalBounds();
    return {rect.width, rect.height};
}

void ConvexShape::setPoints(std::vector<Vectorf> const& points)
{
    const unsigned size = points.size();

    shape_.setPointCount(size);
    for (unsigned i = 0; i < size; ++i) {
        shape_.setPoint(i, {points[i].x, points[i].y});
    }
}

void ConvexShape::draw(Transform const& parent, Camera const& cam)
{
    Graphic::transform(this, parent.position, parent.rotation, parent.origin,
                       cam, shape_);
    tank::Game::window()->SFMLWindow().draw(shape_);
}
}
