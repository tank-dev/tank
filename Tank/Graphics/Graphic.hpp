// Copyright (©) Jamie Bayne, David Truby, David Watson 2013-2014.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt)

#ifndef TANK_GRAPHIC_HPP
#define TANK_GRAPHIC_HPP

#include "../System/Camera.hpp"
#include "../Utility/Vector.hpp"
#include "../Utility/Rect.hpp"
#include "../Geometry/Transform.hpp"

namespace sf
{
class Transformable;
}

namespace tank
{

class Graphic
{
    Vectorf pos_;
    float rot_{0.f};
    Vectorf origin_;
    Vectorf scale_{1.f, 1.f};
    bool relativeToParent_{true};
    bool visible_{true};

public:
    Graphic() = default;
    virtual ~Graphic()
    {
    }

    virtual void setPos(Vectorf pos)
    {
        pos_ = pos;
    }
    virtual Vectorf getPos() const
    {
        return pos_;
    }

    virtual void setRotation(float angle)
    {
        rot_ = angle;
    }
    virtual float getRotation() const
    {
        return rot_;
    }

    virtual void setScale(float scale)
    {
        scale_.x = scale_.y = scale;
    }

    virtual void setScale(Vectorf scale)
    {
        scale_ = scale;
    }

    virtual Vectorf getScale() const
    {
        return scale_;
    }

    virtual void setRelativeToParent(bool relative)
    {
        relativeToParent_ = relative;
    }
    virtual bool isRelativeToParent() const
    {
        return relativeToParent_;
    }

    bool isVisible() const
    {
        return visible_;
    }
    void setVisible(bool visibile)
    {
        visible_ = visibile;
    }

    virtual Vectorf getSize() const = 0;

    virtual void setOrigin(Vectorf o)
    {
        origin_ = o;
    }
    virtual Vectorf getOrigin() const
    {
        return origin_;
    }

    void centreOrigin()
    {
        setOrigin(getSize() / 2);
    }

    /*!
     * \brief Coverts the parent coordinates to local coordinates.
     *
     * \param parentCoords The coordinates to convert.
     *
     * \return Coordinates local to the graphic
     */
    Vectorf graphicFromParentCoords(const Vectorf& parentCoords)
    {
        return (parentCoords - getOrigin()).rotate(-getRotation()) / getScale();
    }

    /*!
     * \brief Get whether the specified point (in local coordinates) in inside
     * the bounds of the graphic.
     *
     * \param localCoords The point in local coordinates to check.
     *
     * \return True if the point is within the area of the graphic
     */
    bool getWithin(const Vectorf& localCoords)
    {
        Vectorf size = getSize();
        return (localCoords.x<0 or localCoords.x> size.x or
                        localCoords.y<0 or localCoords.y> size.y);
    }

    // TODO: Make const
    virtual void draw(Transform const& parent = Transform(),
                      Camera const& = Camera()) = 0;

protected:
    static void transform(Graphic const* g, Vectorf parentPos, float parentRot,
                          Vectorf parentOri, Camera const& cam,
                          sf::Transformable& t);
};
}

#endif /* TANK_GRAPHIC_HPP */
