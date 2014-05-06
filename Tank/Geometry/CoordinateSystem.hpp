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

class RootFrame : public InertialFrame
{
public:
    virtual observing_ptr<InertialFrame> getParentFrame() override;
    virtual Transform getTransformFromParent() override;
};

class CoordinateSystem : public InertialFrame
{
    observing_ptr<InertialFrame> parentFrame_;

    Vectorf pos_;
    float rotation_;
    Vectorf origin_;
    float zoom_;

public:
    CoordinateSystem() = default;

    void setParentFrame(observing_ptr<InertialFrame> frame);

    Vectorf getPos();
    float getRotation();
    Vectorf getOrigin();
    float getZoom();

    void setPos(Vectorf const& pos);
    void setRotation(float rotation);
    void setOrigin(Vectorf const& o);
    void setZoom(float zoom);

    virtual observing_ptr<InertialFrame> getParentFrame() override;
    virtual Transform getTransformFromParent() override;
};

class GraphicalCoordinateSystem : public CoordinateSystem
{
    Vectorf scale_;

public:
    GraphicalCoordinateSystem() = default;

    Vectorf getScale();

    void setScale(Vectorf const& scale);

    void transform(observing_ptr<InertialFrame> cam, sf::Transformable& t);

    virtual Transform getTransformFromParent() override;
};

} // tank

#endif // TANK_COORDINATESYSTEM_HPP
