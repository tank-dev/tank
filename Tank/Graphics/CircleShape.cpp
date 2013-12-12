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

void CircleShape::setScale(float scale)
{
    circleShape_.setScale({scale,scale});
}
void CircleShape::setScale(Vectorf scale)
{
    circleShape_.setScale({scale.x, scale.y});
}
Vectorf CircleShape::getScale() const
{
    auto scale = circleShape_.getScale();
    return { scale.x, scale.y };
}

void CircleShape::setOrigin(Vectorf o)
{
    auto scale = circleShape_.getScale();
    circleShape_.setOrigin({o.x / scale.x, o.y / scale.y});
}

Vectorf CircleShape::getOrigin() const
{
    auto origin = circleShape_.getScale();
    auto scale = circleShape_.getScale();
    return {origin.x * scale.x, origin.y * scale.y};
}

void CircleShape::draw(tank::Vectorf parentPos,
                       float parentRot,
                       tank::Camera const& cam)
{
    /* Model */
    const auto modelOrigin = getOrigin();
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

    setScale({modelScale.x*viewScale.x, modelScale.y * viewScale.y});

    /* Change sprite settings */
    setOrigin({modelOrigin.x + getRadius(), modelOrigin.y + getRadius()});
    circleShape_.setRotation(parentRot);
    circleShape_.setPosition({modelViewPos.x, modelViewPos.y});

    tank::Game::window()->SFMLWindow().draw(circleShape_);

    setOrigin(modelOrigin);
    setScale(modelScale);
}


}
