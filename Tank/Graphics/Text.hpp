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

#ifndef TANK_TEXT_HPP
#define TANK_TEXT_HPP

#include <SFML/Graphics/Text.hpp>
#include "../System/Entity.hpp"
#include "../Utility/Timer.hpp"
#include "../Utility/Vector.hpp"
#include "Font.hpp"

#include <string>

namespace tank
{

class Text : public Graphic
{
    sf::Text text_ {};
public:
    Text() = default;
    Text(const Text&) = default;
    Text(Font& f, unsigned size = 30, std::string text = ""):text_(text, f, size) {}

    ~Text() = default;

    void setFont(Font& f) { text_.setFont(f); }

    void setFontSize(unsigned s) { text_.setCharacterSize(s); }
    unsigned getFontSize() const { return text_.getCharacterSize(); }

    void setText(std::string s) { text_.setString(s); }
    std::string getText() const { return text_.getString(); }

    virtual void setScale(float scale)
    {
        text_.setScale(scale, scale);
    }
    virtual void setScale(Vectorf s)
    {
        text_.setScale(s.x, s.y);
    }
    virtual Vectorf getScale() const
    {
        return {text_.getScale().x, text_.getScale().y};
    }

    virtual void setOrigin(Vectorf o)
    {
        text_.setOrigin(o.x,o.y);
    }
    virtual Vectorf getOrigin() const
    {
        return { text_.getOrigin().x, text_.getOrigin().y };
    }

    virtual Vectorf getSize() const
    {
        return { text_.getLocalBounds().width, text_.getLocalBounds().height };
    }

    // Not implemented
    virtual void setClip(Rectu) {}
    virtual Rectu getClip() const {return {};}

    virtual void setSize(Vectorf) {}
    virtual Vector<unsigned int> getTextureSize() const {return {};}

    virtual void draw(Vectorf parentPos, float parentRot, Vectorf camera = {0,0});
};

}
#endif
