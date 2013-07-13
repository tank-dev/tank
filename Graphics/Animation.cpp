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

#include "Animation.hpp"

#include <algorithm>

namespace tank
{

Animation::Animation(Image const& i, Vector<unsigned int> frameDims)
    : image_ (i)
    , frameDimensions_(frameDims)
    , clip_({0,0,frameDims.x, frameDims.y})
{
}

void Animation::add(std::string name,
                    std::vector<unsigned int> const& frames,
                    unsigned int time)
{
    // Create new AnimationInfo
    animations_.push_back({name, frames, time});
}

void Animation::remove(std::string name)
{
    // Find the animation by name
    auto iter = std::find_if_not(animations_.begin(), animations_.end(),
                                 [&name](AnimationInfo anim)
    {
        return anim.name == (name);
    });

    //Remove the animation from the animations list
    if (iter != animations_.end())
    {
        animations_.erase(iter);
    }
}

void Animation::select(std::string name, bool loop,
                       std::function<void()> callback)
{
    //Check that the requested animation is not already playing
    if (not currentAnimation_ || currentAnimation_->name != name)
    {
        //search for the name requested
        for (auto& anim : animations_)
        {
            if (anim.name == name)
            {
                currentAnimation_ = &anim;
                currentFrame_ = 0;
                loop_ = loop;
                callback_ = callback;

                //Update Animation to reflect changes immediately
                //play();
            }
        }
    }
}

void Animation::play()
{
    //Only play if there is a selected animation
    if (currentAnimation_)
    {
        //Check if we need to change animation frame
        bool playNextFrame = animTimer_.getTicks() > currentAnimation_->time;

        if (playNextFrame)
        {
            ++currentFrame_;

            animTimer_.start(); //Reset timer

            //Check if we've finished the animation
            unsigned const int lastFrame = currentAnimation_->frameList.size();

            if (currentFrame_ >= lastFrame)
            {
                currentFrame_ = 0;

                callback_();

                //If the animation doesn't loop, stop it
                if (not loop_)
                {
                    //Reset all properties (callback, timer, currentFrame, etc)
                    stop();
                }
            }
        }
    }

    //Animation may have ended now. If not, need to set clipping mask for image
    if (currentAnimation_)
    {
        //Start at first frame
        unsigned int frame = currentAnimation_->frameList[currentFrame_];

        //Set clipping rectangle according to current frame
        image_.setClip(frameDimensions_, frame);
    }
}

void Animation::start()
{
    animTimer_.start();
}

void Animation::pause()
{
    animTimer_.pause();
}

void Animation::resume()
{
    if (animTimer_.isPaused() and currentAnimation_ != nullptr)
    {
        animTimer_.resume();
    }
}

void Animation::stop()
{
    animTimer_.stop();

    currentFrame_ = 0;

    //Change appearance to first frame
    play();

    //After appearance has been set, unset member variables
    currentAnimation_ = nullptr;
    callback_ = []{};
}

void Animation::draw(Vectorf parentPos, float parentRot, Vectorf camera)
{
    play();
    image_.draw(parentPos, parentRot, camera);
}

void Animation::setImage(Image const& image, Vector<unsigned int> frameDims)
{
    frameDimensions_ = frameDims;
    image_ = image;
}

void addWalkingAnimation(Animation& anim, unsigned int time)
{
    unsigned int xFrames = anim.getTextureSize().x / anim.getFrameDimensions().x;

    std::vector<unsigned int> up;
    std::vector<unsigned int> right;
    std::vector<unsigned int> down;
    std::vector<unsigned int> left;

    for (unsigned int i = 0; i < xFrames; ++i)
    {
        up.push_back(i);
        right.push_back(i + xFrames);
        down.push_back(i + xFrames * 2);
        left.push_back(i + xFrames * 3);
    }
    anim.add("walk_up", up, time);
    anim.add("walk_right", right, time);
    anim.add("walk_down", down, time);
    anim.add("walk_left", left, time);
}

}
