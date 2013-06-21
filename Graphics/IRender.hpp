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

#pragma once
#ifndef TANK_IRENDER_HPP
#define TANK_IRENDER_HPP

#include <string>

#include "../Utility/Rect.hpp"
#include "../Utility/Vector.hpp"
#include "../Graphics/Texture.hpp"

namespace tank {

//TODO Implement 2D OpenGL to remove stupid dependencies
class IRender
{
public:
    virtual bool initialize() = 0;

    virtual void draw(Texture const* texture,
                      Vectorf const& position) = 0;
    virtual void draw(Texture const* texture,
                      Vectorf const& position,
                      Rect    const& clip)     = 0;

    virtual void drawText(char const* text, Vectorf const& position) = 0;

    virtual void flipDisplay() = 0;

    virtual Texture const* getTexture(char const* name) = 0;
    virtual bool loadImage(char const* name, char const* fileName) = 0;

    virtual ~IRender() {}
};

class NullRender final : public IRender
{
public:
    virtual bool initialize()
    {
        return true;
    }

    virtual void draw(Texture const* texture,
                      Vectorf const& position) override;
    virtual void draw(Texture const* texture,
                      Vectorf const& position,
                      Rect    const& clip) override;

    virtual void drawText(char const* text, Vectorf const& position) override;

    virtual void flipDisplay() override;

    virtual Texture const* getTexture(char const* name) override;
    virtual bool loadImage(char const* name, char const* fileName) override;
};

}

#endif
