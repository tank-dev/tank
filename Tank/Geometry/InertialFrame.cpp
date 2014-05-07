// Copyright (©) Jamie Bayne, David Truby, David Watson 2013-2014.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt)

#include "InertialFrame.hpp"
#include "Transform.hpp"
#include <SFML/Graphics/Transformable.hpp>

namespace tank
{

Transform InertialFrame::getTransform(InertialFrame const* iner) const
{
    // The transformation from root to iner
    Transform tInv;
    // The transformation from root to this
    Transform t = this->getTransformFromParent();

    // Get the transforamation from root to this and the root of this
    InertialFrame const* currentFrame = this;
    InertialFrame const* nextFrame = currentFrame->getParentFrame();
    while (nextFrame != currentFrame)
    {
        if (nextFrame == nullptr)
        {
            throw std::logic_error("A parent is null");
        }
        currentFrame = nextFrame;
        nextFrame = currentFrame->getParentFrame();
        t = currentFrame->getTransformFromParent()(t);
    }
    InertialFrame const* thisRoot = currentFrame;

    if (iner != nullptr)
    {
        // Get the transforamation from root to iner and the root of iner
        currentFrame = iner;
        nextFrame = currentFrame->getParentFrame();
        tInv = currentFrame->getTransformFromParent();
        while (nextFrame != currentFrame)
        {
            if (nextFrame == nullptr)
            {
                throw std::logic_error("A parent is null");
            }
            currentFrame = nextFrame;
            nextFrame = currentFrame->getParentFrame();
            tInv = currentFrame->getTransformFromParent()(tInv);
        }
    }
    // We set the inerRoot to be either the root of iner if it isn't null or to
    // the same a thisRoot if it is.
    InertialFrame const* inerRoot = currentFrame;

    if (inerRoot != thisRoot)
    {
        throw std::domain_error("Incompatible universes");
    }
    return tInv.inverse()(t);
}

} // tank
