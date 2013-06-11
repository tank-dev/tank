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
      _log(nullptr),
      _render(nullptr) {}
//}}}

//{{{Game::~Game()
Game::~Game()
{ 
    log("Closing window");
    delete(_render);
    delete(_window);
    delete(_log);
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
		
		//Create the game log file
        _log = new Logger("game");
		if (!_log->initialize())
		{
			std::cout << "Something is horribly wrong."
				<< std::endl
				<< "The log file has failed to be created."
				<< std::endl;
			return false;
		}

        //Create window
        _window = new Window(640,640);

        //Select PCRender as the rendering engine
        log("Loading rendering engine");

        _render = new PCRender();

        ServiceLocator::provide(_render);  //Make render available on request

        if(!_render->initialize())
        {
            _initialized = false; 
            log("Could not initialize rendering engine");
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
    log("Entering main loop");
    while(_run)
    {
        _frameTimer.start();

        if(_states.empty())
        {
            log("No game state");
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

		//Delay until the next frame so the game stays at 60fps
        if (1000000 / FRAMES_PER_SECOND > _frameTimer.getMicrosecs()) {
            Timer::delay((unsigned long)(1000000 / FRAMES_PER_SECOND - _frameTimer.getTicks()));
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

//{{{bool Game::pushState( State* state )
bool Game::addState(State* state)
{
    std::unique_ptr<State> statePointer = std::unique_ptr<State>(state);
    if(state->initialize())
    {
        log("Loaded state successfully");
        _states.push(std::move(statePointer));

        return true;
    }

    log("Not pushing state");

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
