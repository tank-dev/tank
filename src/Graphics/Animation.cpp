#include "Animation.hpp"

#include <algorithm>

Animation::Animation()
: _texture ( NULL ),
  _currentAnimation( NULL ),
  _currentFrame( 0 ),
  _loop( false ),
  _frameDimensions( {0, 0} ),
  _callback( NULL ),
  _clip( { 0, 0, 0, 0 } ) {}

Animation::Animation( Texture const* t, Vector const& frameDims )
: _texture( t ),
  _currentAnimation( NULL ),
  _currentFrame( 0 ),
  _loop( false ),
  _frameDimensions( frameDims ),
  _callback( NULL ),
  _clip( { 0, 0, ( int )frameDims.x, ( int )frameDims.y } ) { }

//{{{void Animation::add( char const* name,
void Animation::add( char const* name,
                     std::vector<unsigned int> const& frames,
                     unsigned int time )
{
    //Push back a POD-initialized AnimationInfo(name, numframes, time)
    _animations.push_back( { std::string(name), frames, time } );
}
//}}}

//{{{void Animation::remove(char const* name)
void Animation::remove(char const* name)
{
    // Find the animation by name
    std::vector<AnimationInfo>::iterator iter =
        std::find_if( _animations.begin(),
                      _animations.end(),
                      [name]( AnimationInfo anim )->bool
                      { return !anim.name.compare(name); } );

    //Remove the animation from the animations list
    if(iter != _animations.end())
    {
        _animations.erase(iter);
    }
}
//}}}

//{{{void Animation::play( char const* name, bool loop, void (*callback)() )
void Animation::play( char const* name, bool loop, void (*callback)() )
{
    //Check that the requested animation is not already playing
    if(!_currentAnimation || _currentAnimation->name.compare(name) != 0)
    {
        //Find the requested animation
        for(auto iter = _animations.begin(); iter != _animations.end(); ++iter)
        {
            if((*iter).name.compare(name) == 0)
            {
                //Select the animation
                _currentAnimation = &(*iter); 
                _animTimer.start();

                _currentFrame = 0;
                //Save play settings
                _loop = loop;
                _callback = callback;

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
    _animTimer.pause();
}
//}}}

//{{{void Animation::resume()
void Animation::resume()
{
    if( _animTimer.isPaused() && _currentAnimation != NULL )
    {
        _animTimer.resume();
    }
}
//}}}

//{{{void Animation::stop()
void Animation::stop()
{
    _animTimer.stop(); //Set timer to 0

    _currentFrame     = 0;

    //Change appearance to first frame
    //May not be a good idea?
    update(); 

    //Unset member variables 
    _currentAnimation = NULL;
    _callback         = NULL;
}
//}}}

//{{{void Animation::update()
//
//This function could probably use a bit of TLC
void Animation::update()
{
    //Only update if there is an animation playing
    if(_currentAnimation)
    { 
        //Check if we need to change animation frame
        const bool playNextFrame = _animTimer.getTicks() > _currentAnimation->time;

        if(playNextFrame)
        {
            ++_currentFrame;    //Change frame

            _animTimer.start(); //Reset timer

            //Check if we've finished the animation
            unsigned const int lastFrame = _currentAnimation->frameList.size();

            if(_currentFrame >= lastFrame)
            { 
                _currentFrame = 0;

                if(_callback) _callback();

                //If the animation doesn't loop, stop it
                if (!_loop)
                {
                    //Reset all properties (callback, timer, currentFrame, etc)
                    stop();
                }
            }
        }
    }

    if(_currentAnimation)
    { 
        //Start at first frame
        auto frameIter = _currentAnimation->frameList.begin();

        //Move to current frame
        frameIter += _currentFrame;

        //Set clipping rectangle according to current frame
        _clip.x = ( *frameIter ) * _frameDimensions.x;
        _clip.w = _frameDimensions.x;
    }
}
//}}}

//{{{void Animation::draw(IRender *const render, Vector const& pos)
void Animation::draw(IRender *const render, Vector const& pos)
{
    render->draw(_texture, pos, _clip);
}
//}}}

//{{{void Animation::setTexture(Texture const*const texture)
void Animation::setTexture(Texture const*const texture, Vector const& frameDims)
{
    _frameDimensions = frameDims;
    _texture = texture;
} 
//}}}
