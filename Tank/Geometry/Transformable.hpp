#ifndef TANK_TRANSFORMABLE_HPP
#define TANK_TRANSFORMABLE_HPP

#include "../Utility/Vector.hpp"
#include "Transform.hpp"

namespace tank {

class Transformable
{
    Transform transform_;

public:
    virtual ~Transformable() = default;
    Transformable(Vectorf pos = {},
                  float rotation = 0,
                  Vectorf origin = {},
                  Vectorf scale = {1.f, 1.f})
        : transform_{pos, rotation = 0, origin, scale}
    {}
    Transformable(Transformable const&) = default;

    virtual Vectorf getPos() const
    {
        return transform_.position;
    }
    virtual float getRotation() const
    {
        return transform_.rotation;
    }
    virtual Vectorf getOrigin() const
    {
        return transform_.origin;
    }
    virtual Vectorf getScale() const
    {
        return transform_.scale;
    }
    Transform const& getTransform() const
    {
        return transform_;
    }

    virtual void setPos(Vectorf pos)
    {
        transform_.position = pos;
    }
    virtual void setRotation(float rotation)
    {
        transform_.rotation = rotation;
    }
    virtual void setOrigin(Vectorf origin)
    {
        transform_.origin = origin;
    }
    virtual void setScale(float s)
    {
        transform_.scale = {s,s};
    }
    virtual void setScale(Vectorf scale)
    {
        transform_.scale = scale;
    }
    virtual void setTransform(Transform const& t)
    {
        transform_ = t;
    }
};

} /* tank */

#endif /* TANK_TRANSFORMABLE_HPP */
