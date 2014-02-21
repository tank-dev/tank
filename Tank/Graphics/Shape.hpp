// Copyright (©) Jamie Bayne, David Truby, David Watson 2013-2014.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt)

#ifndef TANK_SHAPE_HPP
#define TANK_SHAPE_HPP

#include "Graphic.hpp"
#include "Color.hpp"

namespace tank {

class Shape : public Graphic
{
public:
    virtual void setFillColor(Color c) = 0;
    virtual void setOutlineColor(Color c) = 0;
    virtual void setOutlineThickness(float) = 0;
    virtual Color const& getFillColor() const = 0;
    virtual Color const& getOutlineColor() const = 0;
    virtual float getOutlineThickness() const = 0;
};

}
#endif /* TANK_SHAPE_HPP */
