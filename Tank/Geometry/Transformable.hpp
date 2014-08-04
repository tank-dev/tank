#ifndef TANK_TRANSFORMABLE_HPP
#define TANK_TRANSFORMABLE_HPP

#include "../Utility/Vector.hpp"
#include "Transform.hpp"

namespace tank {

class Transformable
{
    Transform transform_;
    observing_ptr<Transformable> parent_;

public:
    virtual ~Transformable() = default;
    Transformable(Vectorf pos = {},
                  float rotation = 0,
                  Vectorf origin = {},
                  float zoom = 1.f)
        : transform_{pos, rotation, origin, zoom}
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
    virtual float getZoom() const
    {
        return transform_.zoom;
    }

    virtual Vectorf getScale() const
    {
        return {transform_.zoom,transform_.zoom};
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
    virtual void setZoom(float s)
    {
        transform_.zoom = s;
    }
    virtual void setTransform(Transform const& t)
    {
        transform_ = t;
    }

    virtual void setParent(observing_ptr<Transformable> p)
    {
        parent_ = p;
    }
    virtual void removeParent()
    {
        parent_ = nullptr;
    }

    virtual Transform getWorldTransform() const
    {
        if (not parent_) {
            return transform_;
        } else {
            //return transform_(parent_->getWorldTransform());
            return parent_->getWorldTransform()(transform_);
        }
    }
};

} /* tank */

#endif /* TANK_TRANSFORMABLE_HPP */
