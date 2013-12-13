#include "RectangleShape.hpp"
#include "../System/Game.hpp"

namespace tank {

RectangleShape::RectangleShape(Vectorf size)
    : Shape()
    , rectangleShape_({size.x, size.y})
{
}

void RectangleShape::setFillColor(Color c)
{
    rectangleShape_.setFillColor(c);
}
void RectangleShape::setOutlineColor(Color c)
{
    rectangleShape_.setOutlineColor(c);
}
void RectangleShape::setOutlineThickness(float thickness)
{
    rectangleShape_.setOutlineThickness(thickness);
}
Color const& RectangleShape::getFillColor() const
{
    return rectangleShape_.getFillColor();
}
Color const& RectangleShape::getOutlineColor() const
{
    return rectangleShape_.getOutlineColor();
}
float RectangleShape::getOutlineThickness() const
{
    return rectangleShape_.getOutlineThickness();
}

void RectangleShape::setSize(Vectorf size)
{
    rectangleShape_.setSize({size.x, size.y});
}

Vectorf RectangleShape::getSize() const
{
    auto rect = rectangleShape_.getGlobalBounds();
    return {rect.width, rect.height};
}

void RectangleShape::draw(tank::Vectorf parentPos,
                          float parentRot,
                          tank::Camera const& cam)
{
    Graphic::transform(this, parentPos, parentRot, cam, rectangleShape_);
    tank::Game::window()->SFMLWindow().draw(rectangleShape_);
}


}
