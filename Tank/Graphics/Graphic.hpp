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
#include "../Geometry/Transformable.hpp"

namespace sf
{
class Transformable;
}

namespace tank
{

class Graphic : public tank::Transformable
{
    bool visible_{true};

public:
    Graphic() = default;
    virtual ~Graphic() = default;

    bool isVisible() const
    {
        return visible_;
    }
    void setVisible(bool visibile)
    {
        visible_ = visibile;
    }

    virtual Vectorf getSize() const = 0;

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
    Vectorf graphicFromParentCoords(const Vectorf& parentCoords)
    {
        return (parentCoords - getOrigin()).rotate(-getRotation()) / getScale();
    }
     */

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
        return (localCoords.x < 0 or localCoords.x > size.x or
                localCoords.y < 0 or localCoords.y > size.y);
    }

    // TODO: Make const
    virtual void draw() = 0;

protected:
    static void transform(Graphic const* g, sf::Transformable& t);
};
}

#endif /* TANK_GRAPHIC_HPP */
