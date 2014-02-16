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

#include "FrameList.hpp"

#include <algorithm>

namespace tank
{

FrameList::FrameList(Image const& i, Vector<unsigned int> frameDims)
    : image_ (i)
    , frameDimensions_(frameDims)
{
    image_.setClip({0,0,frameDims.x, frameDims.y});
    //image_.setSize(frameDims);
}

void FrameList::add(std::string name,
                    std::vector<unsigned int> const& frames,
                    unsigned int time)
{
    // TODO: validate arguments
    // Create new Animation
    animations_.push_back({name, frames, std::chrono::milliseconds(time)});
}

void FrameList::remove(std::string name)
{
    // Find the animation by name
    auto iter = std::find_if_not(animations_.begin(), animations_.end(),
            [&name](Animation& anim)
            {
            return anim.name == (name);
            });

    //Remove the animation from the animations list
    if (iter != animations_.end())
    {
        animations_.erase(iter);
    }
}

void FrameList::select(std::string name, bool loop,
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
            }
        }
    }
}

void FrameList::refresh()
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

void FrameList::start()
{
    if (not animTimer_.isStarted())
    {
        animTimer_.start();
    }
}

void FrameList::pause()
{
    animTimer_.pause();
}

void FrameList::resume()
{
    if (animTimer_.isPaused() and currentAnimation_ != nullptr)
    {
        animTimer_.resume();
    }
}

void FrameList::stop()
{
    //Change appearance to first frame
    currentFrame_ = 0;
    refresh();

    //Unset member variables
    animTimer_.stop();
    callback_ = []{};
    currentAnimation_ = nullptr;
}

void FrameList::draw(Vectorf parentPos, float parentRot, Camera const& cam)
{
    refresh();
    image_.draw(parentPos, parentRot, cam);
}

void FrameList::setImage(Image const& image, Vector<unsigned int> frameDims)
{
    frameDimensions_ = frameDims;
    image_ = image;
}

void addWalkingFrameList(FrameList& anim, unsigned int time)
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
