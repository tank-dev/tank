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
    sf::ConvexShape shape_;

public:
    ConvexShape() = default;
    ConvexShape(std::vector<Vectorf> const& points);

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
    virtual void setSize(Vectorf);
    virtual Vectorf getSize() const override;

    void setPoints(std::vector<Vectorf> const& points);

    virtual void draw(Transform const& t) override final;
};

}

#endif /* TANK_CONVEXSHAPE_HPP */
