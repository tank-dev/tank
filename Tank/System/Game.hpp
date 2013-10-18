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

#ifndef TANK_GAME_HPP
#define TANK_GAME_HPP

#include <stack>
#include <memory>
#include "../Utility/Timer.hpp"
#include "../Utility/Logger.hpp"
#include "../Utility/observing_ptr.hpp"
#include "IWindow.hpp"
#include "State.hpp"

namespace tank {

/*!
 * \brief Static Game class containing main loop and current state.
 *
 * To start the game engine, call Game::initialize(). This will create the
 * window, and initialize rendering.
 *
 * Once started, you should create a State with Game::makeState<>(). This will
 * both create a state and add it to the top of the state stack.
 *
 * Once there is a state to run, call Game::run() to start the main loop.
 *
 * \see State
 * \see Logger
 */
class Game
{
    static bool initialized_;
    static bool run_;

    static bool popState_;

    static observing_ptr<State> currentState_;
    static std::unique_ptr<IWindow> window_;

    static std::stack<std::unique_ptr<State>> states_;
    static Timer frameTimer_;

public:
    /*!
     * \brief The log. This acts like a stream, remember to finish your log
     * with std::endl.
     */
    static Logger log;
    static unsigned int fps;

    /*!
     * \brief Initializes the game.
     *
     * Creates a window and a rendering context.
     * \param windowSize The window canvas size in pixels.
     * \return True on success.
     */
    static bool initialize(Vector<unsigned int> const& windowSize, int fps = 60);
    /*!
     * \brief Starts the game loop
     */
    static void run();

    /*!
     * \brief This removes the current state at the end of the frame.
     */
    static void popState();

    /*!
     * \brief This creates a game state.
     *
     * \tparam T The type of state.
     * \tparam Args The arguments to pass to create the state.
     * \param args The arguments to create the state.
     *
     * \return A pointer to the state.
     */
    template<typename T, typename... Args>
    static observing_ptr<T> makeState(Args&&... args);

    /*!
     * \brief Return a pointer to the active state
     *
     * \return A pointer to the active state
     */
    static observing_ptr<State> state() { return currentState_; }

    static std::unique_ptr<IWindow> const& window() { return window_; };
private:
    static void handleEvents();
    static void update();
    static void draw();

    Game();
    ~Game();
};

template<typename T, typename... Args>
observing_ptr<T> Game::makeState(Args&&... args)
{
    static_assert(std::is_base_of<State, T>::value,
                  "Class must derive from State");

    std::unique_ptr<T> state {new T(std::forward<Args>(args)...)};
    observing_ptr<T> ptr {state};
    states_.push(std::move(state));
    return ptr;
}

}

#endif
