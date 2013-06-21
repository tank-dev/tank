#pragma once
#ifndef TANK_GAME_HPP
#define TANK_GAME_HPP

#include <stack>
#include <memory>
#include "../Graphics/IRender.hpp"
#include "../System/IWindow.hpp"
#include "../Utility/Timer.hpp"
#include "State.hpp"
#include <SDL/SDL_events.h>
#include "../Utility/Logger.hpp"
#include <iostream>

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
 * Currently, it is required to call Game::close() to clean up after the game
 * has finished, but this requirement should be lifted in later versions.
 * \see State
 * \see Logger
 */
class Game
{
public:
	/*!
	 * \brief Initializes the game.
	 *
     * Creates a window and a rendering context.
     * \param windowSize The window canvas size in pixels.
	 * \return True on success.
	 */
    static bool initialize(Vectori const& windowSize);
	/*!
	 * \brief Starts the game loop
	 */
    static void run();
	/*!
	 * \brief This cleans up after the game.
     *
     * This function should be placed at the end of your program to clean up
     * some of the engine's dependencies
	 */
    static void close();

	/*!
	 * \brief This removes the current state at the end of the frame.
	 */
    static void popState();

	/*!
	 * \brief The log. This acts like a stream, remember to finish your log
	 * with std::endl.
	 */
    static Logger log;

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
    static T* makeState(Args&&... args)
    {
        static_assert(std::is_base_of<State,T>::value, "Class must derive from State");
        T* state = new T(std::forward<Args>(args)...);
        states_.emplace(state);
        return state;
    }

    /*! 
     * \brief Return a reference to the active state
     *
     * \return A reference to the active state
     */
    static State& state() { return *states_.top().get(); }
private:
    static bool initialized_;
    static bool run_;

    //Hacky hacky hacky
    static bool popState_;

    static IWindow* window_;
    static IRender* render_;

    static std::stack<std::unique_ptr<State>> states_;
    static Timer frameTimer_;

    static void handleEvents();
    static void update();
    static void draw();

    Game();
    ~Game(); 
};

}

#endif
