#include "IRender.hpp"

void NullRender::draw(Texture const* texture,
                  Vectorf  const& position) {}
void NullRender::draw(Texture const* texture,
                  Vectorf  const& position,
                  Rect    const& clip) {}

void NullRender::drawText(char const* text, Vectorf const& position) {}

void NullRender::flipDisplay() {}

Texture const* NullRender::getTexture(char const* name)
{
    return nullptr;
}
bool NullRender::loadImage(char const* name, char const* fileName)
{
    return true;
}
