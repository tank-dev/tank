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
    static bool initialize();
    static void run();
    static void close();

    //bool addState(State*);
    static void popState();

	/*! \brief Log a message in the game logfile.
	 *
	 *  \param logStr The first part of the message to be logged.
	 *  \param args The rest of the message.
	 */

    //TODO remove unnecessary accessor
    static Logger& log() {
        return log_;
    }
    static Logger log_;

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
