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
 * Copyright (©) Jamie Bayne, David Truby, David Watson
 */

#pragma once
#ifndef TANK_ANIMATION_HPP
#define TANK_ANIMATION_H

#include <string>
#include <vector>
#include <functional>
#include "../Graphics/IRender.hpp"
#include "../Graphics/Texture.hpp"
#include "../Utility/Vector.hpp"
#include "../Utility/Rect.hpp"
#include "../Utility/Timer.hpp"

namespace tank {

/*!
 * \brief Represents an image with multiple frames and stores animations for that image.
 */
class Animation
{
public:
    Animation() = default;
    /*!
     * \brief Construct an Animation with a Texture.
     * \param t Texture to give the animation.
     * \param frameDims size of each image in the Texture.
     */
    Animation(Texture const* const t, const Vectorf& frameDims) :
        texture_ {t}, frameDimensions_(frameDims), 
        clip_({0,0,(int)frameDims.x, (int)frameDims.y}) {}

    /*!
     * \brief Add an animations
     * \param name String to identify the animation with later.
     * \param frames std::initializer_list of frames.
     * \param frameTime Time between each frame in milliseconds (ms)
     */
    void add(const std::string& name,
             const std::vector<unsigned int>& frames,
             unsigned int frameTime);
    void remove(const std::string& name);

    void select(const std::string& name, bool loop = true, std::function<void()> = []{});

    /*!
     * \brief Called in addition to draw to change the state of an animation.
     */
    void play();

    /*!
     * \brief Draw the animation.
     * Trying to draw an animation without a texture will crash the game!
     * Play must be called as well to change the state of the animation.
     * \param render Render context.
     * \param pos Position at which to draw the texture.
     */
    void draw(IRender* const render, const Vectorf& pos);

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
    void setTexture(Texture const*const texture, Vectorf const& frameDims);


private:
    struct AnimationInfo
    {
        std::string               name;
        std::vector<unsigned int> frameList;
        unsigned int              time;
    };

    Texture const* texture_
    {
        nullptr
    };
    AnimationInfo* currentAnimation_ {nullptr};
    unsigned int currentFrame_ {0};
    Timer animTimer_;
    bool loop_ {false};
    Vectorf frameDimensions_ {0,0};
    std::function<void()> callback_ = []{};
    Rect clip_ {0,0,0,0};
    std::vector<AnimationInfo>  animations_;
};

}

#endif
