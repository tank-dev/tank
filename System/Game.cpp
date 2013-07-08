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
#include <SFML/Window/Event.hpp>
#include <SFML/Window/Keyboard.hpp>
#include "Window.hpp"

namespace tank
{

Logger Game::log {"log.txt"};
const unsigned int Game::FPS {60};
bool Game::initialized_ {false};
bool Game::run_ {false};
bool Game::popState_ {false};
State* Game::currentState_ {nullptr};
std::unique_ptr<IWindow> Game::window_ {nullptr};
std::stack<std::unique_ptr<State>> Game::states_;
Timer Game::frameTimer_;

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
        window_.reset(new Window({wSize.x,wSize.y}));
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

        currentState_ = states_.top().get();

        handleEvents();

        currentState_->update();

        draw();

        if (popState_)
        {
            states_.pop();
            popState_ = false;
        }

		//Delay until the next frame so the game stays at 60fps
        if (1000000 / FPS > frameTimer_.getMicrosecs()) {
            Timer::delayMicrosecs(
                static_cast<unsigned long>(1000000 / 
                                           FPS - frameTimer_.getTicks()));
        }
    }
}

void Game::handleEvents()
{
    sf::Event event;
    //TODO Make this independent of SFML
    while (window_->pollEvent(event))
    {
        switch (event.type)
        {
        case sf::Event::KeyPressed:
        case sf::Event::KeyReleased:
            /*
            if((event.key.code == sf::Keyboard::Key::F4 && event.key.alt)
            {
                run_ = false;
                break;
            }
            */
            //if(!states_.empty())
            //{
                currentState_->handleEvents(event.key.code);
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
    currentState_->draw();

    //Update the screen
    window_->flipDisplay();
}

}
