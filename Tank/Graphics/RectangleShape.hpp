#ifndef TANK_RECTANGLESHAPE_HPP
#define TANK_RECTANGLESHAPE_HPP

#include <SFML/Graphics/RectangleShape.hpp>
#include "Shape.hpp"

namespace tank {

class RectangleShape : public Shape
{
    sf::RectangleShape rectangleShape_;

public:
    RectangleShape(Vectorf size = {});

    virtual void setFillColor(Color colour) override;
    virtual void setOutlineColor(Color colour) override;
    virtual void setOutlineThickness(float) override;
    virtual Color const& getFillColor() const override;
    virtual Color const& getOutlineColor() const override;
    virtual float getOutlineThickness() const override;

    virtual void setSize(Vectorf);
    virtual Vectorf getSize() const override;

    virtual void setOrigin(Vectorf o) override
    {
        rectangleShape_.setOrigin({o.x, o.y});
    }

    virtual Vectorf getOrigin() const override
    {
        auto origin = rectangleShape_.getOrigin();
        return { origin.x, origin.y };
    }

    virtual void draw(Vectorf parentPos = {},
                      float parentRot = 0,
                      Camera const& = Camera()) override;
};

}

#endif /* TANK_RECTANGLESHAPE_HPP */
