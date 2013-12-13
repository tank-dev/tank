#include "CircleShape.hpp"
#include "../System/Game.hpp"

namespace tank {

CircleShape::CircleShape(float radius):Shape(), circleShape_(radius)
{
}

void CircleShape::setFillColor(Color c)
{
    circleShape_.setFillColor(c);
}
void CircleShape::setOutlineColor(Color c)
{
    circleShape_.setOutlineColor(c);
}
void CircleShape::setOutlineThickness(float thickness)
{
    circleShape_.setOutlineThickness(thickness);
}
Color const& CircleShape::getFillColor() const
{
    return circleShape_.getFillColor();
}
Color const& CircleShape::getOutlineColor() const
{
    return circleShape_.getOutlineColor();
}
float CircleShape::getOutlineThickness() const
{
    return circleShape_.getOutlineThickness();
}

Vectorf CircleShape::getSize() const
{
    auto rect = circleShape_.getGlobalBounds();
    return {rect.width, rect.height};
}

void CircleShape::draw(tank::Vectorf parentPos,
                       float parentRot,
                       tank::Camera const& cam)
{
    Graphic::transform(this, parentPos, parentRot, cam, circleShape_);
    Game::window()->SFMLWindow().draw(circleShape_);
}


}
