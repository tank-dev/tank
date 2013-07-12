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

#ifndef TANK_ANIMATION_HPP
#define TANK_ANIMATION_HPP

#include <string>
#include <vector>
#include <functional>
#include "Graphic.hpp"
#include "Image.hpp"
#include "../Utility/Vector.hpp"
#include "../Utility/Rect.hpp"
#include "../Utility/Timer.hpp"

namespace tank
{

/*!
 * \brief Represents an image with multiple frames and stores animations for
 * that image.
 */
class Animation final : public Graphic
{
public:
    Animation() = default;
    /*!
     * \brief Construct an Animation with a Texture.
     * \param t Image to give the animation.
     * \param frameDims size of each image in the Texture.
     */
    Animation(Image const&, Vector<unsigned int> frameDimensions);

    /*!
     * \brief Add an animations
     * \param name String to identify the animation with later.
     * \param frames std::initializer_list of frames.
     * \param frameTime Time between each frame in milliseconds (ms)
     */
    void add(std::string name, const std::vector<unsigned int>& frames,
             unsigned int frameTime);

    void remove(std::string name);

    void select(std::string name, bool loop = true,
                std::function<void()> = []{});

    /*!
     * \brief Update the animation to the current frame. Called by draw
     */
    void play();

    /*!
     * \brief Draw the animation.
     * Trying to draw an animation without a texture will crash the game!
     * Play must be called as well to change the state of the animation.
     * \param pos Position at which to draw the texture.
     */
    void draw(Vectorf parentPos, float parentRot, Vectorf camera = {0, 0}) override;

    /*!
     * \brief Start the animation
     */
    void start();

    /*!
     * \brief Pause the animation.
     */
    void pause();

    /*!
     * \brief Resume the animation.
     */
    void resume();

    /*!
     * \brief Stop the animation.
     * Sets the state of the animation to the first frame.
     */
    void stop();

    /*!
     * \return If the animation is playing.
     */
    bool playing()
    {
        return currentAnimation_;
    }
    std::string currentAnimation()
    {
        return currentAnimation_->name;
    }

    /*!
     * \brief Set the texture of the Animation.
     * \param texture the Texture to set.
     * \param frameDims the dimensions of each image in the texture.
     */
    void setImage(Image const&, Vectoru frameDims);

    virtual void setPos(Vectorf pos) { image_.setPos(pos); }
    virtual Vectorf getPos() const { return image_.getPos(); }

    virtual void setScale(float scale) override
    {
        image_.setScale(scale);
    }
    virtual void setScale(Vectorf scale) override
    {
        image_.setScale(scale);
    }
    virtual Vectorf getScale() const override
    {
        return image_.getScale();
    }

    virtual void drawRelativeToParent(bool relative)
    {
        image_.drawRelativeToParent(relative);
    }
    virtual bool isRelativeToParent() { return image_.isRelativeToParent(); }

    virtual void setRotation(float angle) { image_.setRotation(angle); }
    virtual float getRotation() const { return image_.getRotation(); }

    void setClip(Rectu clip) override { image_.setClip(clip); }
    Rectu getClip() const override { return image_.getClip(); }

    void setOrigin(Vectorf origin) override { image_.setOrigin(origin); }
    Vectorf getOrigin() const override { return image_.getOrigin(); }

    void setSize(Vectorf size) override { image_.setSize(size); }
    Vectorf getSize() const override { return image_.getSize(); }

    virtual Vectoru getTextureSize() const override
    {
        return image_.getTextureSize();
    }
private:
    struct AnimationInfo
    {
        std::string name;
        std::vector<unsigned int> frameList;
        unsigned int time;
    };

    Image image_;
    AnimationInfo* currentAnimation_ {nullptr};
    unsigned int currentFrame_ {0};
    Timer animTimer_;
    bool loop_ {false};
    Vectoru frameDimensions_ {0, 0};
    std::function<void()> callback_ = []{};
    Rectu clip_ {0, 0, 0, 0};
    std::vector<AnimationInfo>  animations_;
};

}

#endif
