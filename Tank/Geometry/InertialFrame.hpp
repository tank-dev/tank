// Copyright (©) Jamie Bayne, David Truby, David Watson 2013-2014.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt)

#ifndef TANK_INERTIALFRAME_HPP
#define TANK_INERTIALFRAME_HPP

#include "../Utility/observing_ptr.hpp"
#include "Transform.hpp"

namespace tank
{

class InertialFrame
{
public:
    InertialFrame() = default;

    /*!
     * \brief This gets the parent frame. 
     *
     * \return The parent inertial frame.
     */
    virtual observing_ptr<InertialFrame> getParentFrame() = 0;

    /*!
     * \brief This gets the transformation that converts from this inertial
     * frame to the parent inertial frame.
     *
     * \return The transformation.
     */
    virtual Transform getTransformFromParent() = 0;

    /*!
     * \brief This gets the transformation that converts from this inertial
     * frame to the inertial frame `inertialFrame`
     *
     * \param iner The inertial frame to transform to
     *
     * \return The transformation.
     */
    Transform getTransform(observing_ptr<InertialFrame> inertialFrame);
};

} // tank

#endif // TANK_INERTIALFRAME_HPP
