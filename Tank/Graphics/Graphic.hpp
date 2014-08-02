// Copyright (©) Jamie Bayne, David Truby, David Watson 2013-2014.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt)

#ifndef TANK_GRAPHIC_HPP
#define TANK_GRAPHIC_HPP

#include "../System/Camera.hpp"
#include "../Utility/Vector.hpp"
#include "../Utility/Rect.hpp"
#include "../Utility/observing_ptr.hpp"

namespace sf
{
class Transformable;
class Shader;
}

namespace tank
{

using Shader = sf::Shader;

class Graphic
{
    Vectorf pos_;
    float rot_ {0.f};
    Vectorf origin_;
    Vectorf scale_ {1.f, 1.f};
    bool relativeToParent_ {true};
    bool visible_ {true};
    observing_ptr<Shader> shader_;

public:
    Graphic() = default;
    virtual ~Graphic() {}

    virtual void setPos(Vectorf pos)
    {
        pos_ = pos;
    }
    virtual Vectorf getPos() const
    {
        return pos_;
    }

    virtual void setRotation(float angle)
    {
        rot_ = angle;
    }
    virtual float getRotation() const
    {
        return rot_;
    }

    virtual void setScale(float scale)
    {
        scale_.x = scale_.y = scale;
    }

    virtual void setScale(Vectorf scale)
    {
        scale_ = scale;
    }

    virtual Vectorf getScale() const
    {
        return scale_;
    }

    void drawRelativeToParent(bool relative)
    {
        relativeToParent_ = relative;
    }
    bool isRelativeToParent() const
    {
        return relativeToParent_;
    }

    bool isVisible() const
    {
        return visible_;
    }
    void setVisible(bool visibile)
    {
        visible_ = visibile;
    }

    virtual Vectorf getSize() const = 0;

    virtual void setOrigin(Vectorf o)
    {
        origin_ = o;
    }
    virtual Vectorf getOrigin() const
    {
        return origin_;
    }

    void centreOrigin()
    {
        setOrigin(getSize()/2);
    }

    // TODO: Make const
    virtual void draw(Vectorf parentPos = {},
                      float parentRot = 0,
                      Vectorf parentOri = {},
                      Camera const& = Camera()) = 0;

    virtual void attachShader(observing_ptr<Shader>);
    virtual void detachShader();
    virtual void detachShader(observing_ptr<Shader>);
    virtual observing_ptr<Shader> getShader();

protected:
    static void transform(Graphic const* g,
                          Vectorf parentPos,
                          float parentRot,
                          Vectorf parentOri,
                          Camera const& cam,
                          sf::Transformable& t);
};

}

#endif /* TANK_GRAPHIC_HPP */
