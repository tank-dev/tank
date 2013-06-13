#pragma once
#ifndef GAME_H
#define GAME_H

#include <stack>
#include <memory>
#include "../Graphics/IRender.hpp"
#include "../System/IWindow.hpp"
#include "../Utility/Timer.hpp"
#include "State.hpp"
#include <SDL/SDL_events.h>
#include "../Utility/Logger.hpp"
#include <iostream>

class Game
{
public:
	/*!
	 * \brief This initilizes the game. It returns true if the game is
	 * successfully initilized.
	 *
	 * \return True on success.
	 */
    static bool initialize();
	/*!
	 * \brief This runs the game.
	 */
    static void run();
	/*!
	 * \brief This quits the game.
	 */
    static void close();

    //bool addState(State*);
	/*!
	 * \brief This removes a state at the end of the frame.
	 */
    static void popState();

    //TODO remove unnecessary accessor
    static Logger& log() {
        return log_;
    }
	/*!
	 * \brief The logger. This acts like a stream, remember to finish your log
	 * with std::endl.
	 */
    static Logger log_;

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
    static T& makeState(Args&&... args)
    {
        static_assert(std::is_base_of<State,T>::value, "Class must derive from State");
        T* state = new T(std::forward<Args>(args)...);
        states_.emplace(state);
        return *state;
    }

    /*! \brief Return a reference to the active state
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

#endif
