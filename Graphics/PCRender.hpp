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

#pragma once
#ifndef TANK_PCRENDER_HPP
#define	TANK_PCRENDER_HPP

#include "IRender.hpp"

#include <map>
#include <string>

struct SDL_Surface;

namespace tank {

class PCRender : public IRender
{
public:
    /* IRender method overrides */
    //Initialization
    virtual bool initialize();

    //Rendering
    virtual void draw(Texture const* texture,
                      Vectorf  const& position);
    virtual void draw(Texture const* texture,
                      Vectorf  const& position,
                      Rect    const& clip);

    virtual void drawText(char const* text, Vectorf const& position);
    virtual void flipDisplay();

    //Image loading/retrieval
    virtual Texture const* getTexture(char const* name);
    virtual bool           loadImage(char const* name, char const* fileName);

    /* Constructor and Destructor */
    PCRender();
    virtual ~PCRender();
private:
    std::map<std::string, Texture> textures_;

    /* Implementation-specific private data */
    SDL_Surface* screen_;
    std::map<std::string, SDL_Surface*> images_;
};

}

#endif
