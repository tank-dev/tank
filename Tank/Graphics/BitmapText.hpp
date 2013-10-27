#ifndef TANK_BITMAPTEXT_HPP
#define TANK_BITMAPTEXT_HPP

#include <climits>
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

    char const* text_ {""};
    Vectorf origin_ {};

public:
    BitmapText(Image const& font, Vectoru glyphDimensions,
               char asciiOffset = 32, unsigned int rowWidth = UINT_MAX);

    void setText(char const* text)
    {
        text_ = text;
    }
    char const* getText()
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
    virtual void setSize(Vectorf size) override;
    /*!
     * \brief Return the rendered glyph size
     *
     * \return The glyph size
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

    virtual void draw(Vectorf parentPos, float parentRot, Vectorf camera = {0,0});
};

}

#endif /* TANK_BITMAPTEXT_HPP */
