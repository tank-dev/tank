#include "Animation.hpp"

#include <algorithm>

Animation::Animation() : texture_ {nullptr}, currentAnimation_ {nullptr},
          currentFrame_ {0}, loop_ {false}, frameDimensions_ {0, 0}, callback_ {nullptr},
          clip_ { 0, 0, 0, 0 }
{}

Animation::Animation(Texture const* t, Vector const& frameDims)
    : texture_(t),
      currentAnimation_(nullptr),
      currentFrame_(0),
      loop_(false),
      frameDimensions_(frameDims),
      callback_(nullptr),
    clip_({ 0, 0, (int)frameDims.x, (int)frameDims.y }) { }

//{{{void Animation::add( char const* name,
void Animation::add(char const* name,
                    std::vector<unsigned int> const& frames,
                    unsigned int time)
{
    //Push back a POD-initialized AnimationInfo(name, numframes, time)
    animations_.push_back({ std::string(name), frames, time });
}
//}}}

//{{{void Animation::remove(char const* name)
void Animation::remove(char const* name)
{
    // Find the animation by name
    std::vector<AnimationInfo>::iterator iter =
        std::find_if(animations_.begin(),
                     animations_.end(),
                     [name](AnimationInfo anim)->bool
    { return !anim.name.compare(name); });

    //Remove the animation from the animations list
    if(iter != animations_.end()) {
        animations_.erase(iter);
    }
}
//}}}

//{{{void Animation::play( char const* name, bool loop, void (*callback)() )
void Animation::play(char const* name, bool loop, void (*callback)())
{
    //Check that the requested animation is not already playing
    if(!currentAnimation_ || currentAnimation_->name.compare(name) != 0) {
        //Find the requested animation
        for(auto iter = animations_.begin(); iter != animations_.end(); ++iter) {
            if((*iter).name.compare(name) == 0) {
                //Select the animation
                currentAnimation_ = &(*iter);
                animTimer_.start();

                currentFrame_ = 0;
                //Save play settings
                loop_ = loop;
                callback_ = callback;

                //Does an initial update to reflect changes immediately
                update();
            }
        }
    }
}
//}}}

//{{{void Animation::pause()
void Animation::pause()
{
    animTimer_.pause();
}
//}}}

//{{{void Animation::resume()
void Animation::resume()
{
    if(animTimer_.isPaused() && currentAnimation_ != nullptr) {
        animTimer_.resume();
    }
}
//}}}

//{{{void Animation::stop()
void Animation::stop()
{
    animTimer_.stop(); //Set timer to 0

    currentFrame_     = 0;

    //Change appearance to first frame
    //May not be a good idea?
    update();

    //Unset member variables
    currentAnimation_ = nullptr;
    callback_         = nullptr;
}
//}}}

//{{{void Animation::update()
//
//This function could probably use a bit of TLC
void Animation::update()
{
    //Only update if there is an animation playing
    if(currentAnimation_) {
        //Check if we need to change animation frame
        const bool playNextFrame = animTimer_.getTicks() > currentAnimation_->time;

        if(playNextFrame) {
            ++currentFrame_;    //Change frame

            animTimer_.start(); //Reset timer

            //Check if we've finished the animation
            unsigned const int lastFrame = currentAnimation_->frameList.size();

            if(currentFrame_ >= lastFrame) {
                currentFrame_ = 0;

                if(callback_) {
                    callback_();
                }

                //If the animation doesn't loop, stop it
                if(!loop_) {
                    //Reset all properties (callback, timer, currentFrame, etc)
                    stop();
                }
            }
        }
    }

    if(currentAnimation_) {
        //Start at first frame
        auto frameIter = currentAnimation_->frameList.begin();

        //Move to current frame
        frameIter += currentFrame_;

        //Set clipping rectangle according to current frame
        clip_.x = (*frameIter) * frameDimensions_.x;
        clip_.w = frameDimensions_.x;
    }
}
//}}}

//{{{void Animation::draw(IRender *const render, Vector const& pos)
void Animation::draw(IRender* const render, Vector const& pos)
{
    render->draw(texture_, pos, clip_);
}
//}}}

//{{{void Animation::setTexture(Texture const*const texture)
void Animation::setTexture(Texture const* const texture, Vector const& frameDims)
{
    frameDimensions_ = frameDims;
    texture_ = texture;
}
//}}}
