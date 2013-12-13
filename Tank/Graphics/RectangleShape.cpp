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

void RectangleShape::setScale(float scale)
{
    rectangleShape_.setScale({scale,scale});
}
void RectangleShape::setScale(Vectorf scale)
{
    rectangleShape_.setScale({scale.x, scale.y});
}
Vectorf RectangleShape::getScale() const
{
    auto scale = rectangleShape_.getScale();
    return { scale.x, scale.y };
}

void RectangleShape::setOrigin(Vectorf o)
{
    auto scale = rectangleShape_.getScale();
    rectangleShape_.setOrigin({o.x / scale.x, o.y / scale.y});
}

Vectorf RectangleShape::getOrigin() const
{
    auto origin = rectangleShape_.getScale();
    auto scale = rectangleShape_.getScale();
    return {origin.x * scale.x, origin.y * scale.y};
}

void RectangleShape::draw(tank::Vectorf parentPos,
                          float parentRot,
                          tank::Camera const& cam)
{
    /* Model */
    const auto modelScale = getScale();
    auto modelPos = getPos();
    auto modelRot = getRotation();
    if(isRelativeToParent())
    {
        modelPos += parentPos;
        modelRot += parentRot;
    }

    /* View */
    const auto viewScale = cam.getZoom();
    const auto viewRot = cam.getRotation();
    const float viewRads = 3.14159265 * viewRot / 180.f;
    auto viewPos = cam.getPos();
    viewPos.x *= viewScale.x;
    viewPos.y *= viewScale.y;

    modelPos -= cam.getOrigin();

    tank::Vectorf modelViewPos;
    modelViewPos.x = modelPos.x * std::cos(viewRads) + modelPos.y * std::sin(viewRads);
    modelViewPos.y = - modelPos.x * std::sin(viewRads) + modelPos.y * std::cos(viewRads);
    modelViewPos.x *= viewScale.x;
    modelViewPos.y *= viewScale.y;
    modelViewPos += cam.getOrigin();
    modelViewPos -= viewPos;

    float modelViewRot = modelRot - viewRot;

    setScale({modelScale.x*viewScale.x, modelScale.y * viewScale.y});

    /* Change sprite settings */
    rectangleShape_.setPosition({modelViewPos.x, modelViewPos.y});
    rectangleShape_.setRotation(modelViewRot);

    tank::Game::window()->SFMLWindow().draw(rectangleShape_);
    setScale(modelScale);
}


}
