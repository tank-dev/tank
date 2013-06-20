#pragma once
#ifndef TANK_GRAPHIC_HPP
#define TANK_GRAPHIC_HPP

#include "../Utility/Vector.hpp"

class Graphic
{
public:
    Graphic() {}
    virtual ~Graphic() {}

    virtual Vectori const& getSize() const = 0;

    virtual void draw(Vectorf const& pos) = 0;
};

#endif /* TANK_GRAPHIC_HPP */
