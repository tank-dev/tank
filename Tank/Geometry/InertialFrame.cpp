// Copyright (©) Jamie Bayne, David Truby, David Watson 2013-2014.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt)

#include "InertialFrame.hpp"
#include "CoordinateFrame.hpp"
#include "Transform.hpp"

#include <boost/range/algorithm.hpp>

namespace tank
{

/*

InertialFrame::~InertialFrame()
{
    // Remove from the parent frame if it has one.
    removeFromHigherachy();
}


void InertialFrame::addChild(observing_ptr<IntertialFrame> child)
{
    children_.push_back(child);
}

void InertialFrame::removeChild(observing_ptr<IntertialFrame> child)
{
    boost::remove(children_, child);
}

observing_ptr<const InertialFrame> InertialFrame::getRootFrame() const
{
    return this;
}

void InertialFrame::setParentFrame(observing_ptr<InertialFrame> frame)
{
    if (parentFrame_)
    {
        parentFrame_->removeChild(this);
    }
    parentFrame_ = frame;
    parentFrame_->addChild(this);
}

observing_ptr<InertialFrame> InertialFrame::getParentFrame() const
{
    return nullptr;
}

Transform InertialFrame::getTransformFromParent() const
{
    return Transform();
}

Transform InertialFrame::getTransformFromRoot() const
{
    return Transform();
}

Transform InertialFrame::getTransform(observing_ptr<const InertialFrame> iner) const
{
    // The transformation from root to iner
    Transform tInv;
    // The transformation from root to this
    Transform t = this->getTransformFromRoot();

    if (iner != nullptr)
    {
        tInv = iner->getTransformFromRoot();
    }

    // We posibly should check that they are living in compatible universes
    //if (inerRoot != thisRoot)
    //{
    //    throw std::domain_error("Incompatible universes");
    //}
    //
    return tInv.inverse()(t);
}

std::vector<observing_ptr<IntertialFrame>> const& InertialFrame::getChildren()
{
    return children_;
}
*/

} // tank
