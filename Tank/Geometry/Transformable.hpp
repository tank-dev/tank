#ifndef TANK_TRANSFORMABLE_HPP
#define TANK_TRANSFORMABLE_HPP

#include "../Utility/Vector.hpp"
#include "Transform.hpp"

namespace tank {

class Transformable
{
    Transform transform_;

public:
    Transformable() = default;
    Transformable(Transformable const&) = default;
    virtual ~Transformable() = default;

    Vectorf getPos() const
    {
        return transform_.position;
    }
    float getRotation() const
    {
        return transform_.rotation;
    }
    Vectorf getOrigin() const
    {
        return transform_.origin;
    }
    float getZoom() const
    {
        return transform_.zoom;
    }
    Vectorf getScale() const
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
    virtual void setZoom(float zoom)
    {
        transform_.zoom = zoom;
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
