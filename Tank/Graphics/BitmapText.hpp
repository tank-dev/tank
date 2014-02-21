// Copyright (©) Jamie Bayne, David Truby, David Watson 2013-2014.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt)

#ifndef TANK_BITMAPTEXT_HPP
#define TANK_BITMAPTEXT_HPP

#include <climits>
#include <string>
#include "Graphic.hpp"
#include "Image.hpp"

namespace tank
{

class BitmapText final : public Graphic
{
    Image font_;
    Vectoru glyphDims_;
    char asciiOffset_;
    unsigned int rowWidth_;
    Rectu clip_;

    // TODO: make std::string
    std::string text_ {""};
    Vectorf origin_;

public:
    BitmapText(Image const& font, Vectoru glyphDimensions,
               char asciiOffset = 32, unsigned int rowWidth = UINT_MAX);

    void setText(std::string text)
    {
        text_ = text;
    }
    std::string getText()
    {
        return text_;
    }

    virtual void setScale(float scale) override
    {
        font_.setScale(scale);
    }
    virtual void setScale(Vectorf scale) override
    {
        font_.setScale(scale);
    }
    virtual Vectorf getScale() const override
    {
        return font_.getScale();
    }

    /*!
     * \brief Set the size of each rendered glyph
     *
     * \param size The size for each glyph
     */
    virtual void setGlyphSize(Vectorf size);
    /*!
     * \brief Return the rendered glyph size
     *
     * \return The glyph size
     */
    virtual Vectorf getGlyphSize() const;

    /*!
     * \brief Return the size of the current string
     */
    virtual Vectorf getSize() const override;

    virtual void setOrigin(Vectorf origin) override
    {
        origin_ = origin;
    }
    virtual Vectorf getOrigin() const override
    {
        return origin_;
    }

    virtual Vector<unsigned int> getTextureSize() const
    {
        return font_.getTextureSize();
    }

    virtual void draw(Vectorf parentPos = {},
                      float parentRot = 0,
                      Camera const& = Camera());
};

}

#endif /* TANK_BITMAPTEXT_HPP */
