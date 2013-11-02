/* This file is part of Tank.
 *
 * Tank is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Lesser General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * Tank is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License and
 * the GNU Lesser General Public Licence along with Tank. If not, see
 * <http://www.gnu.org/licenses/>.
 *
 * Copyright 2013 (©) Jamie Bayne, David Truby, David Watson.
 */

#include "Text.hpp"

namespace tank
{
void Text::draw(Vectorf parentPos, float parentRot, Camera const& cam)
{
    const auto modelScale = getScale();
    Vectorf modelPos = getPos();
    float modelRot = getRotation();

    if(isRelativeToParent())
    {
        modelPos += parentPos;
        modelRot += parentRot;
    }

    const auto viewScale = cam.getZoom();
    const float viewRot = cam.getRotation();
    const float viewRads = 3.14159265 * viewRot / 180.f;

    modelPos -= cam.getOrigin();
    modelPos.x *= viewScale.x;
    modelPos.y *= viewScale.y;
    Vectorf modelViewPos;
    modelViewPos.x = modelPos.x * std::cos(viewRads) + modelPos.y * std::sin(viewRads);
    modelViewPos.y = - modelPos.x * std::sin(viewRads) + modelPos.y * std::cos(viewRads);
    modelViewPos += cam.getOrigin();
    modelViewPos -= cam.getPos();

    float modelViewRot = modelRot - viewRot;

    setScale({modelScale.x*viewScale.x, modelScale.y * viewScale.y});

    text_.setPosition({modelViewPos.x, modelViewPos.y});
    text_.setRotation(modelViewRot);

    Game::window()->SFMLWindow().draw(text_);
    setScale(modelScale);
}
}
