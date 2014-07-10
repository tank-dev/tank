// Copyright (©) Jamie Bayne, David Truby, David Watson 2013-2014.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt)

#ifndef TANK_IMAGE_HPP
#define TANK_IMAGE_HPP

#include <string>
#include <memory>
#include <SFML/Graphics/Sprite.hpp>
#include "../Utility/Vector.hpp"
#include "Texture.hpp"
#include "Graphic.hpp"

namespace tank {

class Image : public Graphic
{
    bool loaded_ {false};
    sf::Sprite sprite_;
    std::shared_ptr<Texture> texture_ {nullptr};

public:
    Image() = default;
    Image(std::string file);

    void load(std::string file);

    virtual Vectorf getSize() const override
    {
        /*auto rect = getClip();
        return {rect.w, rect.h};*/
        auto rect = sprite_.getGlobalBounds();
        return {rect.width, rect.height};
    }

    /*
    virtual void setScale(float scale) override
    {
        sprite_.setScale(scale, scale);
    }
    virtual void setScale(Vectorf scale) override
    {
        sprite_.setScale(scale.x, scale.y);
    }
    virtual Vectorf getScale() const override
    {
        return {sprite_.getScale().x, sprite_.getScale().y};
    }
    */

    void setSize(Vectorf size);

    virtual void setClipByIndex(Vectoru dimensions, unsigned int index,
                         Vectoru spacing = {}, Rectu subClip = {});

    /*!
     * \brief Sets the clip rectangle of the image
     *
     * \param clip The rectangle to clip the image to
     */
    virtual void setClip(Rectu clip)
    {
        sprite_.setTextureRect({static_cast<int>(clip.x),
                                static_cast<int>(clip.y),
                                static_cast<int>(clip.w),
                                static_cast<int>(clip.h)});
    }

    virtual Rectu getClip() const
    {
        auto clip = sprite_.getTextureRect();
        return {static_cast<unsigned int>(clip.left),
                static_cast<unsigned int>(clip.top),
                static_cast<unsigned int>(clip.width),
                static_cast<unsigned int>(clip.height)};
    }

    virtual Vectoru getTextureSize() const
    {
        return {texture_->getSize().x, texture_->getSize().y};
    }

    virtual void draw(Vectorf parentPos = {},
                      float parentRot = 0,
                      Vectorf parentOri = {},
                      Camera const& = Camera()) override;
};

}
#endif /* TANK_IMAGE_HPP */
