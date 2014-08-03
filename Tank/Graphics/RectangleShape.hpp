// Copyright (©) Jamie Bayne, David Truby, David Watson 2013-2014.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt)

#ifndef TANK_RECTANGLESHAPE_HPP
#define TANK_RECTANGLESHAPE_HPP

#include <SFML/Graphics/RectangleShape.hpp>
#include "Shape.hpp"

namespace tank
{

class RectangleShape : public Shape
{
    sf::RectangleShape rectangleShape_;

public:
    RectangleShape(Vectorf size = {});
    RectangleShape(Rectf);

    virtual void setFillColor(Color colour) override;
    virtual void setOutlineColor(Color colour) override;
    virtual void setOutlineThickness(float) override;
    virtual Color const& getFillColor() const override;
    virtual Color const& getOutlineColor() const override;
    virtual float getOutlineThickness() const override;

    virtual void setSize(Vectorf);
    virtual Vectorf getSize() const override;

    virtual void draw() override;
};
}

#endif /* TANK_RECTANGLESHAPE_HPP */
