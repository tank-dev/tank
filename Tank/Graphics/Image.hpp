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

#ifndef TANK_IMAGE_HPP
#define TANK_IMAGE_HPP

#include <string>
#include <memory>
#include <SFML/Graphics/Sprite.hpp>
#include "../Utility/Vector.hpp"
#include "Texture.hpp"
#include "Graphic.hpp"

namespace tank {

class Image final : public Graphic
{
    bool loaded_ {false};
    sf::Sprite sprite_;
    std::shared_ptr<Texture> texture_ {nullptr};

public:
    Image() = default;
    Image(std::string file);

    void load(std::string file);

    virtual void setOrigin(Vectorf origin)
    {
        sprite_.setOrigin({origin.x, origin.y});
    }
    virtual Vectorf getOrigin() const
    {
        return {sprite_.getOrigin().x, sprite_.getOrigin().y};
    }

    virtual Vectorf getSize() const override
    {
        auto rect = getClip();
        return {rect.w, rect.h};
        //auto rect = sprite_.getGlobalBounds();
        //return {rect.width, rect.height};
    }

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

    void setSize(Vectorf size) override;

    virtual void setClip(Vectoru dimensions, unsigned int index);

    virtual void setClip(Rectu clip) override
    {
        sprite_.setTextureRect({static_cast<int>(clip.x),
                                static_cast<int>(clip.y),
                                static_cast<int>(clip.w),
                                static_cast<int>(clip.h)});
    }
    virtual Rectu getClip() const override
    {
        auto clip = sprite_.getTextureRect();
        return {static_cast<unsigned int>(clip.left),
                static_cast<unsigned int>(clip.top),
                static_cast<unsigned int>(clip.width),
                static_cast<unsigned int>(clip.height)};
    }

    virtual Vectoru getTextureSize() const override
    {
        return { texture_->getSize().x, texture_->getSize().y };
    }

    virtual void draw(Vectorf parentPos = {},
                      float parentRot = 0,
                      Camera const& = Camera()) override;
};

}
#endif /* TANK_IMAGE_HPP */
