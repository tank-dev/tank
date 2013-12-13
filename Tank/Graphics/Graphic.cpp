#include "Graphic.hpp"

#include <SFML/Graphics/Transformable.hpp>

namespace tank {

void Graphic::transform(Graphic const* g,
                        Vectorf parentPos,
                        float parentRot,
                        Camera const& cam,
                        sf::Transformable& t)
{
    /// Model ///
    const auto modelScale = g->getScale();
    auto modelPos = g->getPos();
    auto modelRot = g->getRotation();
    if(g->isRelativeToParent())
    {
        modelPos += parentPos;
        modelRot += parentRot;
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
}

} /* tank */
