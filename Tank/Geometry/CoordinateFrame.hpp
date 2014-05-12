// Copyright (©) Jamie Bayne, David Truby, David Watson 2013-2014.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt)

#ifndef TANK_COORDINATEFRAME_HPP
#define TANK_COORDINATEFRAME_HPP

#include "Transform.hpp"
#include "../Utility/observing_ptr.hpp"
#include "../Utility/Vector.hpp"

#include <vector>

namespace tank
{

/*!
 * \brief This stores an intertial frame. It should be used for everything with
 * its own coordinate system.
 */
class CoordinateFrame
{
    Vectorf pos_{0.0f,0.0f};
    float rotation_{0.0f};
    Vectorf origin_{0.0f,0.0f};
    float zoom_{1.0f};

    observing_ptr<CoordinateFrame> parentFrame_;
    std::vector<observing_ptr<CoordinateFrame>> children_;

    /*!
     * \brief This adds a child to the inertial frame.
     *
     * This shouldn't be called from anywhere but CoordinateFrame!
     *
     * \param child A child is a type of Coordinate Frame.
     */
    void addChild(observing_ptr<CoordinateFrame> child);
    /*!
     * \brief This removes a child from the intertial frame
     *
     * This shouldn't be called from anywhere but CoordinateFrame!
     *
     * \param child The Coordinate frame to remove from the children.
     */
    void removeChild(observing_ptr<CoordinateFrame> child);

protected:

public:
    CoordinateFrame() = default;
    CoordinateFrame(Vectorf const& position);

    ~CoordinateFrame();
    void removeFromHigherachy() noexcept;

    /*!
     * \brief This applies the transformation t to the position, rotation and
     * zoom of the coordinate frame.
     *
     * \param t The transformation to apply to the frame.
     */
    void applyTransform(Transform const& t);

    /*!
     * \brief This gets the position of the inertial frame relative to its
     * parent.
     *
     * \return The position relative to its parent.
     */
    virtual Vectorf getPos() const;
    /*!
     * \brief This gets the rotation of the inertial frame relative to its
     * parent.
     *
     * \return The rotation relative to its parent.
     */
    virtual float getRotation() const;
    /*!
     * \brief This gets the origin of the inertial frame.
     *
     * \return The origin relative to itself.
     */
    virtual Vectorf getOrigin() const;
    /*!
     * \brief This gets the zoom of the inertial frame relative to its parent.
     *
     * \return The zoom relative to its parent.
     */
    virtual float getZoom() const;

    /*!
     * \brief This gets the absolute position of the inertial frame relative to
     * the root frame.
     *
     * \return The position relative to its parent.
     */
    virtual Vectorf getAbsolutePos() const;
    /*!
     * \brief This gets the absolute rotation of the inertial frame relative to
     * the root frame.
     *
     * \return The rotation relative to its parent.
     */
    virtual float getAbsoluteRotation() const;
    /*!
     * \brief This gets absolute the zoom of the inertial frame relative to the
     * root frame.
     *
     * \return The zoom relative to its parent.
     */
    virtual float getAbsoluteZoom() const;

    /*!
     * \brief This sets the position of the inertial frame relative to its
     * parent.
     *
     * \param pos The position relative to its parent.
     */
    virtual void setPos(Vectorf const& pos);
    /*!
     * \brief This sets the rotation of the inertial frame relative to its
     * parent.
     *
     * \param rotation The rotation relative to its parent.
     */
    virtual void setRotation(float rotation);
    /*!
     * \brief This sets the origin of the inertial frame.
     *
     * \param o The origin in its own coordinates (ignoring the previous
     * setting of the origin).
     */
    virtual void setOrigin(Vectorf const& o);
    /*!
     * \brief This sets the zoom of the inertial frame relative to its parent.
     *
     * \param zoom The zoom relative to its parent.
     */
    virtual void setZoom(float zoom);

    ////////////////////////////////////////////////////////////////////////////

    /*!
     * \brief Sets the inertial frame that this is relative to.
     *
     * \param frame The frame it is relative to.
     */
    void setParentFrame(observing_ptr<CoordinateFrame> frame = nullptr);
    
    /*!
     * \brief This gets the frame that coordinates in this frame are measured
     * relative to.
     *
     * \return The parent inertial frame.
     */
    observing_ptr<CoordinateFrame> getParentFrame() const;

    /*!
     * \brief This gets the transformation that converts from this inertial
     * frame to the parent frame.
     *
     * \return The transformation.
     */
    Transform getTransformFromParent() const;
    /*!
     * \brief This gets the transformation that converts from this inertial
     * frame to the root frame.
     *
     * \return The transformation.
     */
    Transform getTransformFromRoot() const;

    /*!
     * \brief This gets the transformation that converts from this inertial
     * frame to the inertial frame `iner` or the root inertial frame if iner is
     * null.
     *
     * \param iner The inertial frame to transform to (defaults to nullptr).
     *
     * \return The transformation.
     */
    Transform getTransform(
            observing_ptr<const CoordinateFrame> iner = nullptr) const;

    // It seems for completeness we should have a get children function, so
    // I've implemented it but I don't know where it will be used so I've
    // commented it out.
    //std::vector<observing_ptr<CoordinateFrame>> const& getChildren();
};

} // tank

#endif // TANK_COORDINATEFRAME_HPP
