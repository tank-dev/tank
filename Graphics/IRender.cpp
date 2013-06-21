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
 * Copyright 2013 (©) Jamie Bayne, David Truby, David Watson
 */

#include "IRender.hpp"

namespace tank {

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

}
