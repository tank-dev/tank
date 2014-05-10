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

/*!
 * /brief This is a templates of an intertial frame.
 */
class InertialFrame
{
public:
    InertialFrame() = default;

    /*!
     * \brief This gets the root frame for this inertial frame.
     *
     * \return The root of the inertial frame.
     */
    virtual observing_ptr<const InertialFrame> getRootFrame() const = 0;

    /*!
     * \brief This gets the frame that coordinates in this frame are measured
     * relative to.
     *
     * \return The parent inertial frame.
     */
    virtual observing_ptr<const InertialFrame> getParentFrame() const = 0;

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
    Transform getTransform(observing_ptr<const InertialFrame> iner= nullptr) const;
};

} // tank

#endif // TANK_INERTIALFRAME_HPP
