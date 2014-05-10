// Copyright (©) Jamie Bayne, David Truby, David Watson 2013-2014.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt)

#ifndef TANK_COORDINATESYSTEM_HPP
#define TANK_COORDINATESYSTEM_HPP

#include "InertialFrame.hpp"

#include "../Utility/observing_ptr.hpp"
#include "../Utility/Vector.hpp"

namespace tank
{

/*!
 * \brief This is a root inertial frame, it is the ether.
 */
class RootFrame : public InertialFrame
{
public:
    virtual observing_ptr<const InertialFrame> getRootFrame() const override;
    virtual observing_ptr<const InertialFrame> getParentFrame() const override;
    virtual Transform getTransformFromParent() const override;
};

/*!
 * \brief This stores an intertial frame. It should be used for everything with
 * its own coordinate system.
 */
class CoordinateFrame : public InertialFrame
{
    observing_ptr<InertialFrame> parentFrame_;

    Vectorf pos_{0.0f,0.0f};
    float rotation_{0.0f};
    Vectorf origin_{0.0f,0.0f};
    float zoom_{1.0f};

public:
    CoordinateFrame() = default;
    CoordinateFrame(Vectorf const& position);

    /*!
     * \brief Sets the inertial frame that this is relative to.
     *
     * \param frame The frame it is relative to.
     */
    void setParentFrame(observing_ptr<InertialFrame> frame);
    /*!
     * \brief This checks to see if this inertial frame has the same root as
     * `frame`. If it doesn't then it sets frame as the parent.
     *
     * \param frame The potential candidate for parent.
     */
    void setParentFrameIfNotSameRoot(observing_ptr<InertialFrame> frame);

    /*!
     * \brief This gets the position of the inertial frame relative to its parent.
     *
     * \return The position relative to its parent.
     */
    virtual Vectorf getPos() const;
    /*!
     * \brief This gets the rotation of the inertial frame relative to its parent.
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
     * \brief This sets the position of the inertial frame relative to its parent.
     *
     * \param pos The position relative to its parent.
     */
    virtual void setPos(Vectorf const& pos);
    /*!
     * \brief This sets the rotation of the inertial frame relative to its parent.
     *
     * \param rotation The rotation relative to its parent.
     */
    virtual void setRotation(float rotation);
    /*!
     * \brief This sets the origin of the inertial frame.
     *
     * \param o The origin in its own coordinates (ignoring the previous setting of the origin).
     */
    virtual void setOrigin(Vectorf const& o);
    /*!
     * \brief This sets the zoom of the inertial frame relative to its parent.
     *
     * \param zoom The zoom relative to its parent.
     */
    virtual void setZoom(float zoom);
    
    virtual observing_ptr<const InertialFrame> getRootFrame() const override;
    virtual observing_ptr<const InertialFrame> getParentFrame() const override;
    virtual Transform getTransformFromParent() const override;
};

/*!
 * \brief This is an inertial frame specifically for graphics as they can set
 * their x-scale and y-scale independently.
 */
class GraphicalCoordinateFrame : public CoordinateFrame
{
    Vectorf scale_{1.0f, 1.0f};

public:
    GraphicalCoordinateFrame() = default;

    /*!
     * \brief This gets the position of the inertial frame relative to its parent.
     *
     * \return The position relative to its parent.
     */
    virtual Vectorf getPos() const;
    /*!
     * \brief This gets the rotation of the inertial frame relative to its parent.
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
     * \brief Gets the scale of the coordinate frame.
     *
     * \return The scale of the coordinate frame.
     */
    virtual Vectorf getScale() const;

    /*!
     * \brief This sets the position of the inertial frame relative to its parent.
     *
     * \param pos The position relative to its parent.
     */
    virtual void setPos(Vectorf const& pos);
    /*!
     * \brief This sets the rotation of the inertial frame relative to its parent.
     *
     * \param rotation The rotation relative to its parent.
     */
    virtual void setRotation(float rotation);
    /*!
     * \brief This sets the origin of the inertial frame.
     *
     * \param o The origin in its own coordinates (ignoring the previous setting of the origin).
     */
    virtual void setOrigin(Vectorf const& o);
    /*!
     * \brief This sets the zoom of the inertial frame relative to its parent.
     *
     * \param zoom The zoom relative to its parent.
     */
    virtual void setZoom(float zoom);
    /*!
     * \brief Sets the scale of the coordinate frame.
     *
     * \param scale The scale of the coordinate frame.
     */
    virtual void setScale(Vectorf const& scale);

    /*!
     * \brief Sets the inertial frame that this is relative to.
     *
     * \param frame The frame it is relative to.
     */
    void setParentFrame(observing_ptr<InertialFrame> frame);
    /*!
     * \brief This checks to see if this inertial frame has the same root as
     * `frame`. If it doesn't then it sets frame as the parent.
     *
     * \param frame The potential candidate for parent.
     */
    void setParentFrameIfNotSameRoot(observing_ptr<InertialFrame> frame);
    
    /*!
     * \brief This gets the root frame for this inertial frame.
     *
     * \return The root of the inertial frame.
     */
    observing_ptr<const InertialFrame> getRootFrame() const;
    /*!
     * \brief This gets the frame that coordinates in this frame are measured
     * relative to.
     *
     * \return The parent inertial frame.
     */
    observing_ptr<const InertialFrame> getParentFrame() const;
    /*!
     * \brief This gets the transformation that converts from this inertial
     * frame to the parent inertial frame.
     *
     * \return The transformation.
     */
    Transform getTransformFromParent() const;
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

#endif // TANK_COORDINATESYSTEM_HPP
