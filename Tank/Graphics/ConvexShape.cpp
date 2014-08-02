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

Vectorf ConvexShape::getSize() const
{
    auto rect = convexShape_.getGlobalBounds();
    return {rect.width, rect.height};
}

void ConvexShape::setFillColor(Color c)
{
    convexShape_.setFillColor(c);
}
void ConvexShape::setOutlineColor(Color c)
{
    convexShape_.setOutlineColor(c);
}
void ConvexShape::setOutlineThickness(float thickness)
{
    convexShape_.setOutlineThickness(thickness);
}
Color const& ConvexShape::getFillColor() const
{
    return convexShape_.getFillColor();
}
Color const& ConvexShape::getOutlineColor() const
{
    return convexShape_.getOutlineColor();
}
float ConvexShape::getOutlineThickness() const
{
    return convexShape_.getOutlineThickness();
}

void ConvexShape::setPoints(std::vector<Vectorf> const& points)
{
    const unsigned size = points.size();

    convexShape_.setPointCount(size);
    for (unsigned i = 0; i < size; ++i) {
        convexShape_.setPoint(i, {points[i].x, points[i].y});
    }
}

void ConvexShape::draw(Vectorf parentPos, float parentRot, Vectorf parentOri,
                       Camera const& cam)
{
    Graphic::transform(this, parentPos, parentRot, parentOri, cam,
                       convexShape_);
    tank::Game::window()->SFMLWindow().draw(convexShape_);
}
}
