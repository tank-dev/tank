// Copyright (©) Jamie Bayne, David Truby, David Watson 2013-2014.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt)

#ifndef TANK_CIRCLESHAPE_HPP
#define TANK_CIRCLESHAPE_HPP

#include <SFML/Graphics/CircleShape.hpp>
#include "Shape.hpp"

namespace tank
{

class CircleShape : public Shape
{
    sf::CircleShape shape_;

public:
    CircleShape(float radius = 0);

    void setRadius(float radius)
    {
        shape_.setRadius(radius);
    }
    virtual void setFillColor(Color colour) override
    {
        shape_.setFillColor(colour);
    }
    virtual void setOutlineColor(Color colour) override
    {
        shape_.setOutlineColor(colour);
    }
    virtual void setOutlineThickness(float pixels) override
    {
        shape_.setOutlineThickness(pixels);
    }
    virtual void setOpacity(uint8_t) override;
    virtual void setFillOpacity(uint8_t) override;
    virtual void setOutlineOpacity(uint8_t) override;
    float getRadius() const
    {
        return shape_.getRadius();
    }
    virtual Color const& getFillColor() const override
    {
        return shape_.getFillColor();
    }
    virtual Color const& getOutlineColor() const override
    {
        return shape_.getOutlineColor();
    }
    virtual float getOutlineThickness() const override
    {
        return shape_.getOutlineThickness();
    }
    virtual uint8_t getFillOpacity() const override
    {
        return shape_.getFillColor().a;
    }
    virtual uint8_t getOutlineOpacity() const override
    {
        return shape_.getOutlineColor().a;
    }

    virtual Vectorf getSize() const override;

    virtual void draw(Transform const& t) override;
};
}

#endif /* TANK_CICLESHAPE_HPP */
