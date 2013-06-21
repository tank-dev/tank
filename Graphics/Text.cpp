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

#include "../System/State.hpp"

namespace tank
{

Text::Text(Vectorf const& pos, std::string text, unsigned int duration)
    :Entity(pos),
     text_(text),
     duration_(duration)
{
    //std::string sText(cText);
    displayTimer_.start();
}

Text::~Text()
{
}

void Text::update()
{
    if (duration_ != 0 && displayTimer_.getTicks() >= duration_)
    {
        remove();
    }
}

void Text::draw(IRender* const render)
{
    //TODO Make this work properly
    render->drawText(text_.c_str(), getPos());
}

}
