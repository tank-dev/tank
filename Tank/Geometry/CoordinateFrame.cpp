// Copyright (©) Jamie Bayne, David Truby, David Watson 2013-2014.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt)

#include "CoordinateFrame.hpp"
#include <SFML/Graphics/Transformable.hpp>

#include <boost/range/algorithm.hpp>
#include <boost/range/algorithm_ext.hpp>

namespace tank
{

CoordinateFrame::~CoordinateFrame()
{
    removeFromHigherachy();
}

CoordinateFrame::CoordinateFrame(Vectorf const& position)
    : pos_(position)
{}

void CoordinateFrame::applyTransform(Transform const& t)
{
    setPos(t(getPos()));
    setRotation(t.getRotation() + getRotation());
    setZoom(t.getZoom() * getZoom());
}

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


Vectorf CoordinateFrame::getAbsolutePos() const
{
    Transform t = getParentFrame()->getTransform();
    return t(getPos());
}

float CoordinateFrame::getAbsoluteRotation() const
{
    Transform t = getParentFrame()->getTransform();
    return t.getRotation() + getRotation();
}

float CoordinateFrame::getAbsoluteZoom() const
{
    Transform t = getParentFrame()->getTransform();
    return t.getZoom() * getZoom();
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

////////////////////////////////////////////////////////////////////////////////

void CoordinateFrame::removeFromHigherachy() noexcept
{
    if (parentFrame_)
    {
        parentFrame_->removeChild(this);
    }
    Transform t = getTransformFromParent();
    for (auto itr = children_.begin(); itr != children_.end(); ++itr)
    {
        (*itr)->applyTransform(t);
        (*itr)->setParentFrame(parentFrame_);
    }
}

void CoordinateFrame::addChild(observing_ptr<CoordinateFrame> child)
{
    children_.push_back(child);
}

void CoordinateFrame::removeChild(observing_ptr<CoordinateFrame> child)
{
    boost::remove_erase(children_, child);
}


void CoordinateFrame::setParentFrame(observing_ptr<CoordinateFrame> frame)
{
    if (parentFrame_)
    {
        parentFrame_->removeChild(this);
    }
    parentFrame_ = frame;
    if (frame)
    {
        frame->addChild(this);
    }
    
}

observing_ptr<CoordinateFrame> CoordinateFrame::getParentFrame() const
{
    return parentFrame_;
}

Transform CoordinateFrame::getTransformFromParent() const
{
    return Transform(getRotation(), getPos() - getOrigin().rotate(getRotation()), getZoom());
}

Transform CoordinateFrame::getTransformFromRoot() const
{
    // TODO: implement caching
    if (parentFrame_ == nullptr)
    {
        // If we don't have a parent get the transform that this represents
        return getTransformFromParent();
    }
    else
    {
        // If we do have a parent we apply the root from parent transform to
        // the parent from this transform
        return getParentFrame()->getTransformFromRoot()(getTransformFromParent());
    }
}

Transform CoordinateFrame::getTransform(
        observing_ptr<const CoordinateFrame> iner) const
{
    // The transformation from root to iner
    Transform tInv;
    // The transformation from root to this
    Transform t = this->getTransformFromRoot();

    if (iner != nullptr)
    {
        tInv = iner->getTransformFromRoot();
    }

    return tInv.inverse()(t);
}

//std::vector<observing_ptr<CoordinateFrame>> const& CoordinateFrame::getChildren() 
//{
//    return children_;
//}
} // tank
