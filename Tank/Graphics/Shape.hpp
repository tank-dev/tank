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
