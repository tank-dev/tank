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

    virtual InertialFrame const* getRootFrame() const = 0;

    /*!
     * \brief This gets the parent frame. 
     *
     * \return The parent inertial frame.
     */
    virtual InertialFrame const* getParentFrame() const = 0;

    /*!
     * \brief This gets the transformation that converts from this inertial
     * frame to the parent inertial frame.
     *
     * \return The transformation.
     */
    virtual Transform getTransformFromParent() const = 0;

    /*!
     * \brief This gets the transformation that converts from this inertial
     * frame to the inertial frame `iner` or the root inertial frame it iner is
     * null.
     *
     * \param iner The inertial frame to transform to, this defaults to null.
     *
     * \return The transformation.
     */
    Transform getTransform(InertialFrame const* iner= nullptr) const;
};

} // tank

#endif // TANK_INERTIALFRAME_HPP
