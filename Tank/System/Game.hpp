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
#include "Window.hpp"
#include "World.hpp"

namespace tank {

/*!
 * \brief Static Game class containing main loop and current world.
 *
 * To start the game engine, call Game::initialize(). This will create the
 * window, and initialize rendering.
 *
 * Once started, you should create a World with Game::makeWorld<>(). This will
 * both create a world and add it to the top of the world stack.
 *
 * Once there is a world to run, call Game::run() to start the main loop.
 *
 * \see World
 * \see Logger
 */
class Game
{
    static bool initialized_;
    static bool run_;

    static bool popWorld_;

    static observing_ptr<World> currentWorld_;
    static std::unique_ptr<Window> window_;

    static std::stack<std::unique_ptr<World>> worlds_;
    static Timer frameTimer_;
    static std::unique_ptr<World> newWorld_;

public:
    /*!
     * \brief The log. This acts like a standard stream (cout), remember to
     * finish your log with std::endl.
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
     * \brief This removes the current world at the end of the frame.
     */
    static void popWorld();

    /*!
     * \brief This creates a game world.
     *
     * \tparam T The type of world.
     * \tparam Args The arguments to pass to create the world.
     * \param args The arguments to create the world.
     *
     * \return A pointer to the world.
     */
    template<typename T, typename... Args>
    static observing_ptr<T> makeWorld(Args&&... args);

    /*!
     * \brief Return a pointer to the active world.
     *
     * \return A pointer to the active world.
     */
    static observing_ptr<World> world() { return currentWorld_; }

    /*!
     * \brief Return a reference to a pointer to the Window.
     *
     * \return The window.
     */
    static std::unique_ptr<Window> const& window() { return window_; };
private:
    static void handleEvents();
    static void update();
    static void draw();

    Game();
    ~Game();
};

template<typename T, typename... Args>
observing_ptr<T> Game::makeWorld(Args&&... args)
{
    static_assert(std::is_base_of<World, T>::value,
                  "Class must derive from World");

    std::unique_ptr<T> world {new T(std::forward<Args>(args)...)};
    observing_ptr<T> ptr {world};
    //worlds_.push(std::move(world));
    newWorld_.reset(world.release());
    return ptr;
}

}

#endif
