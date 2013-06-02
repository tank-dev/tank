#include "Game.hpp"

#include <iostream>
#include "ServiceLocator.hpp"
#include "PCRender.hpp"

#include "Window.hpp"

#define FRAMES_PER_SECOND 60

/* ---------------------------- *
 * Constructor and Destructor
 * ---------------------------- */

//{{{Game::Game()
Game::Game()
: _initialized (false),
  _run         (true),
  _deleteState (false),
  _render      (NULL),
  _currentState(NULL) {}
  //}}}

//{{{Game::~Game()
Game::~Game()
{
    while(!_states.empty())
    {
        delete(_states.top());
        _states.pop();
    }

    delete(_render);
    delete(Window::Instance());
}//}}}

/* ---------------------------- *
 * Initialization
 * ---------------------------- */

//{{{bool Game::initialize()
bool Game::initialize()
{
    if(!_initialized)
    {
        _initialized = true;

        //Create window
        if(Window::Instance()->Initialize() == 0)
        {
            _initialized = false;
        }

        //Select PCRender as the rendering engine
        std::cout << "Loading rendering engine" << std::endl;

        _render = new PCRender();

        ServiceLocator::provide (_render); //Make render available on request

        if(!_render->initialize())
        {
            _initialized = false;
        }

        std::cout << "Game initialized successfully" << std::endl;
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

        _currentState = _states.top();

        handleEvents();

        //Update current state
        _currentState->update();

        draw();

        if(_deleteState)
        {
            delete _currentState;
            _deleteState = false;
        }

        //Wait to force constant framerate
        while(_frameTimer.getTicks() < 1000/FRAMES_PER_SECOND && _run)
        {
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
                if(_currentState)
                {
                    _currentState->handleEvents(&event.key);
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
    if(state->initialize())
    {
        std::cout << "Loaded state successfully" << std::endl;
        _states.push(state);

        return true;
    }

    //This is sort of evil, but makes sense in the grand scheme of things:
    delete(state);

    std::cout << "Not pushing state" << std::endl;

    return false;
}//}}}

//{{{void Game::popState()
void Game::popState()
{
    _deleteState = true;
    _states.pop();
}//}}}

/* ----------------------------------- *
 * Singleton stuff
 * TODO Make this not a singleton
 * ----------------------------------- */

//{{{Singleton
Game *Game::_instance = NULL;
Game *Game::Instance()
{
    if(_instance == NULL)
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
    _currentState->draw(_render);

    //Update the screen
    _render->flipDisplay();

}//}}}
