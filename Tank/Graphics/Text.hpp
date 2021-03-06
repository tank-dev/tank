// Copyright (©) Jamie Bayne, David Truby, David Watson 2013-2014.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt)

#ifndef TANK_TEXT_HPP
#define TANK_TEXT_HPP

#include <SFML/Graphics/Text.hpp>
#include "../System/Entity.hpp"
#include "../Utility/Timer.hpp"
#include "../Utility/Vector.hpp"
#include "Font.hpp"
#include "Color.hpp"

#include <string>

namespace tank
{

class Text : public Graphic
{
    sf::Text text_;

public:
    Text() = default;
    Text(const Text&) = default;
    Text(Font& f, unsigned size = 30, std::string text = "")
            : text_(text, f, size)
    {
    }

    ~Text() = default;

    void setFont(Font& f)
    {
        text_.setFont(f);
    }

    void setFontSize(unsigned s)
    {
        text_.setCharacterSize(s);
    }
    unsigned getFontSize() const
    {
        return text_.getCharacterSize();
    }

    void setText(std::string s)
    {
        text_.setString(s);
    }
    std::string getText() const
    {
        return text_.getString();
    }

    virtual Vectorf getSize() const
    {
        return {text_.getLocalBounds().width, text_.getLocalBounds().height};
    }

    virtual void setColor(const Color& color)
    {
        text_.setColor(color);
    }

    virtual void draw(Vectorf parentPos = {}, float parentRot = 0,
                      Vectorf parentOri = {},
                      Camera const& = Camera()) override;
};
}
#endif
