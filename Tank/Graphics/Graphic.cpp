// Copyright (©) Jamie Bayne, David Truby, David Watson 2013-2014.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt)

#include <exception>
#include <SFML/Graphics/Transformable.hpp>
#include <SFML/Graphics/Shader.hpp>
#include "Graphic.hpp"

namespace tank {

void Graphic::attachShader(observing_ptr<sf::Shader> shader)
{
    shader_ = shader;
}

void Graphic::detachShader(observing_ptr<sf::Shader> shader)
{
    if (shader_ == shader) {
        detachShader();
    } else {
        throw std::invalid_argument("Shader was not attached to graphic");
    }
}

void Graphic::detachShader()
{
    shader_ = nullptr;
}

observing_ptr<sf::Shader> Graphic::getShader()
{
    return shader_;
}


void Graphic::transform(Graphic const* g,
                        Vectorf parentPos,
                        float parentRot,
                        Vectorf parentOri,
                        Camera const& cam,
                        sf::Transformable& t)
{
    /// Model ///

    const auto modelScale = g->getScale();
    auto modelPos = g->getPos();
    auto modelRot = g->getRotation();
    auto modelOri = g->getOrigin();

    if(g->isRelativeToParent())
    {
        modelPos = modelPos.rotate(parentRot);
        modelPos += parentPos;
        modelRot += parentRot;
        //modelOri += parentOri;
    }



    /// View ///
    const auto viewScale = cam.getZoom();
    const auto viewRot = cam.getRotation();
    auto viewPos = cam.getPos();
    viewPos.x *= viewScale.x;
    viewPos.y *= viewScale.y;

    // Move to origin
    modelPos -= cam.getOrigin();

    Vectorf modelViewPos;
    // Rotate
    modelViewPos = modelPos.rotate(viewRot);
    // Scale
    modelViewPos.x *= viewScale.x;
    modelViewPos.y *= viewScale.y;
    // Translate
    modelViewPos -= viewPos.rotate(viewRot);

    // Move from origin
    modelViewPos += cam.getOrigin();

    float modelViewRot = modelRot + viewRot;

    /// Change sprite settings ///
    t.setScale({modelScale.x * viewScale.x, modelScale.y * viewScale.y});
    t.setPosition({modelViewPos.x, modelViewPos.y});
    t.setRotation(modelViewRot);
    t.setOrigin({modelOri.x, modelOri.y});
}

} /* tank */
