// Copyright (©) Jamie Bayne, David Truby, David Watson 2013-2014.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt)

#ifndef TANK_CAMERA_HPP
#define TANK_CAMERA_HPP

#include "../Utility/Vector.hpp"

namespace tank
{

class Camera
{
    float rot_{0};
    Vectorf pos_;
    Vectorf origin_;
    Vectorf zoom_{1, 1};

public:
    Vectorf getPos() const
    {
        return pos_;
    }
    void setPos(Vectorf pos)
    {
        pos_ = pos;
    }

    float getRotation() const
    {
        return rot_;
    }
    void setRotation(float rot)
    {
        rot_ = rot;
    }

    Vectorf getOrigin() const
    {
        return origin_;
    }
    void setOrigin(Vectorf o)
    {
        origin_ = o;
    }

    Vectorf getZoom() const
    {
        return zoom_;
    }
    void setZoom(float z)
    {
        zoom_.x = z;
        zoom_.y = z;
    }
    void setZoom(Vectorf z)
    {
        zoom_ = z;
    }

    Vectorf worldFromScreenCoords(Vectorf const& screenCoords)
    {
        return (screenCoords - getOrigin()).rotate(-getRotation()) / getZoom();
    }

    Camera();

private:
};

} /* tank */

#endif /* TANK_CAMERA_HPP */
