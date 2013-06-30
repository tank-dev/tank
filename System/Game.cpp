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

#include "Game.hpp"

#include <iostream>
#include <GL/glew.h>
#include <SFML/Window/Event.hpp>
#include <SFML/Window/Keyboard.hpp>
#include "Window.hpp"

namespace tank
{

Logger Game::log {"log.txt"};
IWindow* Game::window_ {nullptr};
bool Game::initialized_ {false};
bool Game::run_ {false};
bool Game::popState_ {false};
const unsigned int Game::FPS {60};
Timer Game::frameTimer_;
std::stack<std::unique_ptr<State>> Game::states_;

//This shouldn't be necessary, eventually...
void Game::close()
{
    log << "Closing window" << std::endl;
    delete window_;
}

/* ---------------------------- *
 * Initialization
 * ---------------------------- */

//TODO Handle errors with exceptions
bool Game::initialize(Vector<unsigned int> const& wSize)
{
    if (not initialized_)
    {
        initialized_ = true;

        //Create window
        window_ = new Window({wSize.x,wSize.y});

        //Select PCRender as the rendering engine
        log << "Loading rendering engine" << std::endl;

        if(glewInit() != GLEW_OK)
        {
            throw std::runtime_error("Could not initialise GLEW");
        }
    }

    return initialized_;
}

/* ----------------------------------- *
 * Main Game Loop
 * ----------------------------------- */

void Game::run()
{
    if (run_)
    {
        return;
    }

    run_ = true;
    log << "Entering main loop" << std::endl;
    while (run_)
    {
        frameTimer_.start();

        if (states_.empty())
        {
            log << "No game state" << std::endl;
            run_ = false;
            break;
        }

        handleEvents();

        //Update current state
        states_.top()->update();

        draw();

        if (popState_)
        {
            states_.pop();
            popState_ = false;
        }

		//Delay until the next frame so the game stays at 60fps
        if (1000000 / FPS > frameTimer_.getMicrosecs()) {
            Timer::delayMicrosecs(static_cast<unsigned long>(1000000 / FPS - frameTimer_.getTicks()));
        }
    }
}

void Game::handleEvents()
{
    sf::Event event;
    //TODO Make this independent of SDL
    while (window_->pollEvent(event))
    {
        switch (event.type)
        {
        case sf::Event::KeyPressed:
        case sf::Event::KeyReleased:
            /*if((event.key.code == sf::Keyboard::Key::F4 && event.key.alt)
            {
                run_ = false;
                break;
            }*/
            //if(!states_.empty())
            //{
                states_.top()->handleEvents(event.key.code);
            //}
            break;
        case sf::Event::GainedFocus:
            draw();
            break;
        case sf::Event::Closed:
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

/*bool Game::addState(State* state)
{
    std::unique_ptr<State> statePointer = std::unique_ptr<State>(state);
    if(state->initialize())
    {
        log << "Loaded state successfully" << std::endl;
        states_.push(std::move(statePointer));

        return true;
    }

    log << "Not pushing state" << std::endl;

    return false;
}*/

void Game::popState()
{
    popState_ = true;
}

/* --------------------------- *
 * Update and draw functions
 * --------------------------- */

void Game::update()
{
}

void Game::draw()
{
    //Draw current state
    states_.top()->draw();

    //Update the screen
    window_->flipDisplay();
}

}
