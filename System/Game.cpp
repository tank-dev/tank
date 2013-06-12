#include "Game.hpp"

#include <iostream>
#include "../Graphics/PCRender.hpp"
#include "ServiceLocator.hpp"
#include "Window.hpp"

#define FRAMES_PER_SECOND 60

/* ---------------------------- *
 * Constructor and Destructor
 * ---------------------------- */

Game::Game()
    : initialized_(false),
      run_(true),
      popState_(false),
      render_(nullptr) {}

Game::~Game()
{ 
    log() << "Closing window";
    delete(render_);
    delete(window_);
}

/* ---------------------------- *
 * Initialization
 * ---------------------------- */

//TODO Handle errors with exceptions
bool Game::initialize()
{
    if(!initialized_)
    {
        initialized_ = true;

        //Create window
        window_ = new Window(640,640);

        //Select PCRender as the rendering engine
        log() << "Loading rendering engine";

        render_ = new PCRender();

        ServiceLocator::provide(render_);  //Make render available on request

        if(!render_->initialize())
        {
            initialized_ = false; 
            log() << "Could not initialize rendering engine";
        }
    }

    return initialized_;
}

/* ----------------------------------- *
 * Main Game Loop
 * ----------------------------------- */

void Game::run()
{
    log() << "Entering main loop";
    while(run_)
    {
        frameTimer_.start();

        if(states_.empty())
        {
            log() << "No game state";
            run_ = false;
            break;
        }

        handleEvents();

        //Update current state
        states_.top()->update();

        draw();

        if(popState_)
        {
            states_.pop();
            popState_ = false;
        }

		//Delay until the next frame so the game stays at 60fps
        if (1000000 / FRAMES_PER_SECOND > frameTimer_.getMicrosecs()) {
            Timer::delay((unsigned long)(1000000 / FRAMES_PER_SECOND - frameTimer_.getTicks()));
        }
    }
}

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
                run_ = false;
                break;
            }
            if(!states_.empty())
            {
                states_.top()->handleEvents(&event.key);
            }

            break;
        case SDL_VIDEOEXPOSE:
            draw();
            break;
        case SDL_QUIT:
            run_ = false;
            break;
        default:
            break;
        }
    }
}

/* ----------------------------------- *
 * State management
 * ----------------------------------- */

bool Game::addState(State* state)
{
    std::unique_ptr<State> statePointer = std::unique_ptr<State>(state);
    if(state->initialize())
    {
        log() << "Loaded state successfully";
        states_.push(std::move(statePointer));

        return true;
    }

    log() << "Not pushing state";

    return false;
}

void Game::popState()
{
    popState_ = true;
}

/* ----------------------------------- *
 * Singleton stuff
 * TODO Make this not a singleton
 * ----------------------------------- */

Game* Game::instance_ = nullptr;
Game* Game::Instance()
{
    if(instance_ == nullptr)
    {
        instance_ = new Game;
    }
    return instance_;
}

/* --------------------------- *
 * Update and draw functions
 * May be useful later?
 * --------------------------- */

void Game::update()
{
}

void Game::draw()
{
    //Draw current state
    states_.top()->draw(render_);

    //Update the screen
    render_->flipDisplay();

}
