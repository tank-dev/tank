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
    virtual InertialFrame const* getRootFrame() const override;
    virtual InertialFrame const* getParentFrame() const override;
    virtual Transform getTransformFromParent() const override;
};

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

    void setParentFrame(observing_ptr<InertialFrame> frame);
    void setParentFrameIfNotSameRoot(observing_ptr<InertialFrame> frame);

    virtual Vectorf getPos() const;
    virtual float getRotation() const;
    virtual Vectorf getOrigin() const;
    virtual float getZoom() const;

    virtual void setPos(Vectorf const& pos);
    virtual void setRotation(float rotation);
    virtual void setOrigin(Vectorf const& o);
    virtual void setZoom(float zoom);
    
    virtual InertialFrame const* getRootFrame() const override;
    virtual InertialFrame const* getParentFrame() const override;
    virtual Transform getTransformFromParent() const override;
};

class GraphicalCoordinateFrame : public CoordinateFrame
{
    Vectorf scale_{1.0f, 1.0f};

public:
    GraphicalCoordinateFrame() = default;

    virtual Vectorf getScale() const;

    virtual void setScale(Vectorf const& scale);

    void transform(InertialFrame const* cam, sf::Transformable& t) const;

    virtual Transform getTransformFromParent() const override;
};

} // tank

#endif // TANK_COORDINATESYSTEM_HPP
