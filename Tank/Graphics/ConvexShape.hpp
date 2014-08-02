// Copyright (©) Jamie Bayne, David Truby, David Watson 2013-2014.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt)

#ifndef TANK_POLYGONSHAPE_HPP
#define TANK_POLYGONSHAPE_HPP

#include <SFML/Graphics/ConvexShape.hpp>
#include "Shape.hpp"

namespace tank
{

class ConvexShape : public Shape
{
    sf::ConvexShape convexShape_;

public:
    ConvexShape() = default;
    ConvexShape(std::vector<Vectorf> const& points);
    virtual void setFillColor(Color colour) override final;
    virtual void setOutlineColor(Color colour) override final;
    virtual void setOutlineThickness(float) override final;
    virtual Color const& getFillColor() const override final;
    virtual Color const& getOutlineColor() const override final;
    virtual float getOutlineThickness() const override final;

    virtual Vectorf getSize() const override final;

    void setPoints(std::vector<Vectorf> const& points);

    virtual void draw(Vectorf parentPos = {}, float parentRot = 0,
                      Vectorf parentOri = {},
                      Camera const& = Camera()) override final;
};
}

#endif /* TANK_CONVEXSHAPE_HPP */
