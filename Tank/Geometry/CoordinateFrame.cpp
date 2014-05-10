// Copyright (©) Jamie Bayne, David Truby, David Watson 2013-2014.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt)

#include "CoordinateFrame.hpp"
#include <SFML/Graphics/Transformable.hpp>

namespace tank
{

observing_ptr<const InertialFrame> RootFrame::getRootFrame() const
{
    return this;
}

observing_ptr<const InertialFrame> RootFrame::getParentFrame() const
{
    return this;
}

Transform RootFrame::getTransformFromParent() const
{
    return Transform();
}

////////////////////////////////////////////////////////////////////////////////

CoordinateFrame::CoordinateFrame(Vectorf const& position)
    : pos_(position)
{}

Vectorf CoordinateFrame::getPos() const
{
    return pos_;
}

float CoordinateFrame::getRotation() const
{
    return rotation_;
}

Vectorf CoordinateFrame::getOrigin() const
{
    return origin_;
}

float CoordinateFrame::getZoom() const
{
    return zoom_;
}

void CoordinateFrame::setPos(Vectorf const& pos)
{
    pos_ = pos;
}

void CoordinateFrame::setRotation(float rotation)
{
    rotation_ = rotation;
}

void CoordinateFrame::setOrigin(Vectorf const& o)
{
    origin_ = o;
}

void CoordinateFrame::setZoom(float zoom)
{
    zoom_ = zoom;
}

void CoordinateFrame::setParentFrame(observing_ptr<InertialFrame> frame)
{
    parentFrame_ = frame;
}

void CoordinateFrame::setParentFrameIfNotSameRoot(observing_ptr<InertialFrame> frame)
{
    observing_ptr<const InertialFrame> frameRoot = frame->getRootFrame();
    observing_ptr<const InertialFrame> thisRoot = getRootFrame();
    if (frameRoot != thisRoot or thisRoot == nullptr)
    {
        parentFrame_ = frame;
    }
}

observing_ptr<const InertialFrame> CoordinateFrame::getRootFrame() const
{
    observing_ptr<const InertialFrame> parentFrame_ = getParentFrame();
    if (parentFrame_)
    {
        return getParentFrame()->getRootFrame();
    }
    else
    {
        return nullptr;
    }
}

observing_ptr<const InertialFrame> CoordinateFrame::getParentFrame() const
{
    return parentFrame_;
}

Transform CoordinateFrame::getTransformFromParent() const
{
    return Transform(getRotation(), getPos() - getOrigin().rotate(getRotation()), getZoom());
}

////////////////////////////////////////////////////////////////////////////////

Vectorf GraphicalCoordinateFrame::getPos() const
{
    return CoordinateFrame::getPos();
}

float GraphicalCoordinateFrame::getRotation() const
{
    return CoordinateFrame::getRotation();
}

Vectorf GraphicalCoordinateFrame::getOrigin() const
{
    return CoordinateFrame::getOrigin();
}

float GraphicalCoordinateFrame::getZoom() const
{
    return CoordinateFrame::getZoom();
}

Vectorf GraphicalCoordinateFrame::getScale() const
{
    return scale_;
}


void GraphicalCoordinateFrame::setPos(Vectorf const& pos)
{
    return CoordinateFrame::setPos(pos);
}

void GraphicalCoordinateFrame::setRotation(float rotation)
{
    return CoordinateFrame::setRotation(rotation);
}

void GraphicalCoordinateFrame::setOrigin(Vectorf const& o)
{
    return CoordinateFrame::setOrigin(o);
}

void GraphicalCoordinateFrame::setZoom(float zoom)
{
    return CoordinateFrame::setZoom(zoom);
}

void GraphicalCoordinateFrame::setScale(Vectorf const& scale)
{
    scale_ = scale;
}


void GraphicalCoordinateFrame::setParentFrame(observing_ptr<InertialFrame> frame)
{
    return CoordinateFrame::setParentFrame(frame);
}

void GraphicalCoordinateFrame::setParentFrameIfNotSameRoot(observing_ptr<InertialFrame> frame)
{
    return CoordinateFrame::setParentFrameIfNotSameRoot(frame);
}

observing_ptr<const InertialFrame> GraphicalCoordinateFrame::getRootFrame() const
{
    return CoordinateFrame::getRootFrame();
}

observing_ptr<const InertialFrame> GraphicalCoordinateFrame::getParentFrame() const
{
    return CoordinateFrame::getParentFrame();
}

Transform GraphicalCoordinateFrame::getTransformFromParent() const
{
    return Transform(getRotation(),
                     getPos() - getOrigin().rotate(getRotation()),
                     getZoom(), getScale());
}

Transform GraphicalCoordinateFrame::getTransform(observing_ptr<const InertialFrame> iner) const
{
    return CoordinateFrame::getTransform(iner);
}

} // tank
