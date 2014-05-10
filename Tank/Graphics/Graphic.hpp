// Copyright (©) Jamie Bayne, David Truby, David Watson 2013-2014.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt)

#ifndef TANK_GRAPHIC_HPP
#define TANK_GRAPHIC_HPP

#include "../Geometry/CoordinateFrame.hpp"
#include "../System/Camera.hpp"
#include "../Utility/Vector.hpp"
#include "../Utility/Rect.hpp"

namespace sf
{
    class Transformable;
}

namespace tank {

class Graphic : public GraphicalCoordinateFrame
{
    bool visible_ {true};

public:
    Graphic() = default;
    virtual ~Graphic() {}

    bool isVisible() const
    {
        return visible_;
    }
    void setVisibile(bool visibile)
    {
        visible_ = visibile;
    }

    virtual Vectorf getSize() const = 0;

    void centreOrigin()
    {
        setOrigin(getSize()/2);
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
        return (localCoords.x < 0 or localCoords.x > size.x
                or localCoords.y < 0 or localCoords.y > size.y);
    }

    // TODO: Make const
    virtual void draw(Transform const& t) = 0;
    // TODO: Make const
    virtual void draw(observing_ptr<const Camera> = nullptr);
};

}

#endif /* TANK_GRAPHIC_HPP */
