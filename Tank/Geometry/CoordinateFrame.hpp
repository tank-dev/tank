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
    virtual InertialFrame const* getParentFrame() const override;
    virtual Transform getTransformFromParent() const override;
};

class CoordinateFrame : public InertialFrame
{
    observing_ptr<InertialFrame> parentFrame_;

    Vectorf pos_;
    float rotation_;
    Vectorf origin_;
    float zoom_;

public:
    CoordinateFrame() = default;

    void setParentFrame(observing_ptr<InertialFrame> frame);

    Vectorf getPos() const;
    float getRotation() const;
    Vectorf getOrigin() const;
    float getZoom() const;

    void setPos(Vectorf const& pos);
    void setRotation(float rotation);
    void setOrigin(Vectorf const& o);
    void setZoom(float zoom);

    virtual InertialFrame const* getParentFrame() const override;
    virtual Transform getTransformFromParent() const override;
};

class GraphicalCoordinateFrame : public CoordinateFrame
{
    Vectorf scale_;

public:
    GraphicalCoordinateFrame() = default;

    Vectorf getScale() const;

    void setScale(Vectorf const& scale);

    void transform(InertialFrame const* cam, sf::Transformable& t) const;

    virtual Transform getTransformFromParent() const override;
};

} // tank

#endif // TANK_COORDINATESYSTEM_HPP
