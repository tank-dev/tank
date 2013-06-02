#pragma once
#ifndef ANIMATION_H
#define ANIMATION_H

#include <string>
#include <vector>
#include "IRender.hpp"
#include "Rect.hpp"
#include "Vector.hpp"
#include "Texture.hpp"
#include "Timer.hpp"

/* Animation class
 *
 * {{{Description:
 *
 *      Based on FlashPunk's FP.graphics.Sprite class
 *
 *      Represents an image with multiple frames, and stores any number of named 
 *      animations for that image. To use, first create an [Animation], either
 *      constructing it with a [Texture] and the dimensions of a frame, or
 *      setting them later with *setTexture*.
 *
 *      NOTE: Trying to *draw* an [Animation] without a texture WILL crash the
 *            game
 *
 *
 *
 *      To add animations to the [Animation], use add(name, frames, frameTime)
 *      where:
 *
 *          name      - string to identify the animation with later
 *          frames    - initializer_list of frames. I.E. {1,2,3} to create an
 *                      animation that plays frame 1, then 2, then 3.
 *          frameTime - time between each frame in milliseconds (ms)
 *
 *
 *
 *      NOTE: Currently, *draw* does not change an [Animation]'s state. Hence,
 *            when you want to draw an animation call *update* as well.
 *
 *            This offers two benefits: efficiency when using [Animation] as a
 *            clipping tool (no actual animating) and separating actual animation
 *            from drawing (useful when pausing a game)
 *
 *      You can also *pause*, *resume* and *stop* animations, and ask if it is
 *      *playing*.
 *
 *      NOTE: *stop* will set the state of the [Animation] to the first frame of the
 *            current animation.
 *
 * }}}
 *
 */

class Animation
{
public:
    void add   (char const* name,
                std::vector<unsigned int> const& frames,
                unsigned int frameTime);
    void remove(char const* name);

    void play  (char const* name, bool loop = true, void (*callback)() = NULL);
    void update();
    void draw  (IRender *const, Vector const& pos);

    void resume();
    void pause ();
    void stop  ();
    
    bool playing() { return _currentAnimation; }
    std::string currentAnimation() { return _currentAnimation->name; }

    void setTexture(Texture const*, Vector const& frameDims );

    //Constructor and Destructor
    Animation();
    Animation( Texture const*const t, Vector const& frameDims );
    ~Animation() {}
private:
    //{{{struct AnimationInfo
    struct AnimationInfo
    {
        std::string               name;
        std::vector<unsigned int> frameList;
        unsigned int              time;
    }; //}}}

    Texture       const * _texture;
    AnimationInfo       * _currentAnimation;
    unsigned int          _currentFrame;
    Timer                 _animTimer;
    bool                  _loop;
    Vector                _frameDimensions;
    void                  (*_callback)();

    Rect                 _clip;

    std::vector<AnimationInfo>  _animations;
};
#endif
