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
     * \brief Not implemented
     */
    virtual void setSize(Vectorf size) override {};

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

    /*!
     * \brief Not implemented
     */
    virtual void setClip(Rectu) override {}

    /*!
     * \brief Not implemented
     *
     * \return {0,0,0,0}
     */
    virtual Rectu getClip() const override { return {}; }

    virtual Vector<unsigned int> getTextureSize() const override
    {
        return font_.getTextureSize();
    }

    virtual void draw(Vectorf parentPos = {},
                      float parentRot = 0,
                      Camera const& = Camera());
};

}

#endif /* TANK_BITMAPTEXT_HPP */
