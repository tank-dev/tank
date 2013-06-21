#ifndef TANK_GRAPHIC_HPP
#define TANK_GRAPHIC_HPP

#include "../Utility/Vector.hpp"

namespace tank {

class Graphic
{
public:
    Graphic() {}
    virtual ~Graphic() {}

    virtual Vectorf getSize() const = 0;

    virtual void draw(Vectorf const& pos, float angle = 0,
                      Vectorf const& camera = {0,0}) = 0;
};

}

#endif /* TANK_GRAPHIC_HPP */
