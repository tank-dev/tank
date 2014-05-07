// Copyright (©) Jamie Bayne, David Truby, David Watson 2013-2014.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt)

#ifndef TANK_CIRCLESHAPE_HPP
#define TANK_CIRCLESHAPE_HPP

#include <SFML/Graphics/CircleShape.hpp>
#include "Shape.hpp"

namespace tank {

class CircleShape : public Shape
{
    sf::CircleShape circleShape_;

public:
    CircleShape(float radius = 0);

    void setRadius(float radius) { circleShape_.setRadius(radius); }
    float getRadius() const { return circleShape_.getRadius(); }

    virtual void setFillColor(Color colour) override;
    virtual void setOutlineColor(Color colour) override;
    virtual void setOutlineThickness(float) override;
    virtual Color const& getFillColor() const override;
    virtual Color const& getOutlineColor() const override;
    virtual float getOutlineThickness() const override;

    virtual Vectorf getSize() const override;

    virtual void draw(Transform const& t) override;
};

}

#endif /* TANK_CICLESHAPE_HPP */
