// Copyright (©) Jamie Bayne, David Truby, David Watson 2013-2014.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt)

#include "CoordinateSystem.hpp"
#include <SFML/Graphics/Transformable.hpp>

namespace tank
{

observing_ptr<InertialFrame> RootFrame::getParentFrame()
{
    return this;
}

Transform RootFrame::getTransformFromParent()
{
    return Transform();
}

////////////////////////////////////////////////////////////////////////////////

void CoordinateSystem::setParentFrame(observing_ptr<InertialFrame> frame)
{
    parentFrame_ = frame;
}

Vectorf CoordinateSystem::getPos()
{
    return pos_;
}

float CoordinateSystem::getRotation()
{
    return rotation_;
}

Vectorf CoordinateSystem::getOrigin()
{
    return origin_;
}

float CoordinateSystem::getZoom()
{
    return zoom_;
}

void CoordinateSystem::setPos(Vectorf const& pos)
{
    pos_ = pos;
}

void CoordinateSystem::setRotation(float rotation)
{
    rotation_ = rotation;
}

void CoordinateSystem::setOrigin(Vectorf const& o)
{
    origin_ = o;
}

void CoordinateSystem::setZoom(float zoom)
{
    zoom_ = zoom;
}

observing_ptr<InertialFrame> CoordinateSystem::getParentFrame()
{
    return parentFrame_;
}

Transform CoordinateSystem::getTransformFromParent()
{
    return Transform(getRotation(), getPos() - getOrigin().rotate(getRotation()), getZoom());
}

////////////////////////////////////////////////////////////////////////////////

Vectorf GraphicalCoordinateSystem::getScale()
{
    return scale_;
}

void GraphicalCoordinateSystem::setScale(Vectorf const& scale)
{
    scale_ = scale;
}

void GraphicalCoordinateSystem::transform(
                        observing_ptr<InertialFrame> cam,
                        sf::Transformable& t)
{
    getTransform(cam).transform(t);
/*
{
    /// Model ///

    const auto modelScale = g->getScale();
    auto modelPos = g->getPos();
    auto modelRot = g->getRotation();
    auto modelOri = g->getOrigin();

    if(g->isRelativeToParent())
    {
        modelPos = modelPos.rotate(parentRot);
        modelPos += parentPos;
        modelRot += parentRot;
        //modelOri += parentOri;
    }



    /// View ///
    const auto viewScale = cam.getZoom();
    const auto viewRot = cam.getRotation();
    auto viewPos = cam.getPos();
    viewPos.x *= viewScale.x;
    viewPos.y *= viewScale.y;

    // Move to origin
    modelPos -= cam.getOrigin();

    Vectorf modelViewPos;
    // Rotate
    modelViewPos = modelPos.rotate(viewRot);
    // Scale
    modelViewPos.x *= viewScale.x;
    modelViewPos.y *= viewScale.y;
    // Translate
    modelViewPos -= viewPos.rotate(viewRot);

    // Move from origin
    modelViewPos += cam.getOrigin();

    float modelViewRot = modelRot + viewRot;

    /// Change sprite settings ///
    t.setScale({modelScale.x * viewScale.x, modelScale.y * viewScale.y});
    t.setPosition({modelViewPos.x, modelViewPos.y});
    t.setRotation(modelViewRot);
    t.setOrigin({modelOri.x, modelOri.y});
}
*/
}

Transform GraphicalCoordinateSystem::getTransformFromParent()
{
    return Transform(getRotation(), getPos() - getOrigin().rotate(getRotation()), getZoom(), getScale());
}

} // tank
