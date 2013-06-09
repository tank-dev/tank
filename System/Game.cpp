#include "Game.hpp"

#include <iostream>
#include "../Graphics/PCRender.hpp"
#include "ServiceLocator.hpp"
#include "Window.hpp"

#define FRAMES_PER_SECOND 60

/* ---------------------------- *
 * Constructor and Destructor
 * ---------------------------- */

//{{{ Game::Game()
Game::Game()
    : _initialized(false),
      _run(true),
      _popState(false),
      _render(nullptr) {}
//}}}

//{{{Game::~Game()
Game::~Game()
{ 
    std::cout << "Closing window" << std::endl;
    delete(_render);
    delete(_window);
}//}}}

/* ---------------------------- *
 * Initialization
 * ---------------------------- */

//{{{bool Game::initialize()
//TODO Handle errors with exceptions
bool Game::initialize()
{
    if(!_initialized)
    {
        _initialized = true;

        //Create window
        _window = new Window(640,640);

        //Select PCRender as the rendering engine
        std::cout << "Loading rendering engine" << std::endl;

        _render = new PCRender();

        ServiceLocator::provide(_render);  //Make render available on request

        if(!_render->initialize())
        {
            _initialized = false; 
            std::cout << "Could not initialize rendering engine" << std::endl;
        }
    }

    return _initialized;
}//}}}

/* ----------------------------------- *
 * Main Game Loop
 * ----------------------------------- */

//{{{void Game::run()
void Game::run()
{
    std::cout << "Entering main loop" << std::endl;
    while(_run)
    {
        _frameTimer.start();

        if(_states.empty())
        {
            std::cout << "No game state" << std::endl;
            _run = false;
            break;
        }

        handleEvents();

        //Update current state
        _states.top()->update();

        draw();

        if(_popState)
        {
            _states.pop();
            _popState = false;
        }

		/* This is horrific, I added a delay function into the timer to avoid this
        //Wait to force constant framerate
        while(_frameTimer.getTicks() < 1000/FRAMES_PER_SECOND && _run)
        {
        }
		*/
		if (1000 / FRAMES_PER_SECOND > _frameTimer.getTicks()) {
			Timer::delay((unsigned long)(1000 / FRAMES_PER_SECOND - _frameTimer.getTicks()));
		}
    }
}//}}}

//{{{void Game::handleEvents()
void Game::handleEvents()
{
    SDL_Event event;
    //TODO Make this independent of SDL
    while(SDL_PollEvent(&event))
    {
        switch(event.type)
        {
        case SDL_KEYUP:
        case SDL_KEYDOWN:

            if((event.key.keysym.sym == SDLK_F4 && event.key.keysym.mod & KMOD_ALT)
                    || (event.key.keysym.sym == SDLK_w  && event.key.keysym.mod & KMOD_CTRL))
            {
                _run = false;
                break;
            }
            if(!_states.empty())
            {
                _states.top()->handleEvents(&event.key);
            }

            break;
        case SDL_VIDEOEXPOSE:
            draw();
            break;
        case SDL_QUIT:
            _run = false;
            break;
        default:
            break;
        }
    }
}//}}}

/* ----------------------------------- *
 * State management
 * ----------------------------------- */

//{{{bool Game::pushState( GameState* state )
bool Game::addState(GameState* state)
{
    std::unique_ptr<GameState> statePointer = std::unique_ptr<GameState>(state);
    if(state->initialize())
    {
        std::cout << "Loaded state successfully" << std::endl;
        _states.push(std::move(statePointer));

        return true;
    }

    std::cout << "Not pushing state" << std::endl;

    return false;
}//}}}

//{{{void Game::popState()
void Game::popState()
{
    _popState = true;
}//}}}

/* ----------------------------------- *
 * Singleton stuff
 * TODO Make this not a singleton
 * ----------------------------------- */

//{{{Singleton
Game* Game::_instance = nullptr;
Game* Game::Instance()
{
    if(_instance == nullptr)
    {
        _instance = new Game;
    }
    return _instance;
}
//}}}

/* --------------------------- *
 * Update and draw functions
 * May be useful later?
 * --------------------------- */

void Game::update()
{
}

//{{{void Game::draw()
void Game::draw()
{
    //Draw current state
    _states.top()->draw(_render);

    //Update the screen
    _render->flipDisplay();

}//}}}
