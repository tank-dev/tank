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

class Game
{
public:
    static Game* Instance();
    ~Game();

    bool initialize();
    void run();

    //bool addState(State*);
    void popState();

	/**
	 * @brief Log a message in the game logfile.
	 *
	 * @param logStr The first part of the message to be logged.
	 * @param args The rest of the message.
	 */
	template<typename... Args>
    void log(const std::string& logStr, Args&&... args);

    template<typename T, typename... Args>
    T& makeState(Args&&... args)
    {
        static_assert(std::is_base_of<State,T>::value, "Class must derive from State");
        T* state = new T(std::forward<Args>(args)...);
        _states.emplace(state);
        return *state;
    }

    State& state();
private:
    bool _initialized;
    bool _run;

    //Hacky hacky hacky
    bool _popState;

    Logger   _log;
    IWindow* _window;
    IRender* _render;

    std::stack<std::unique_ptr<State>> _states;
    Timer _frameTimer;

    void handleEvents();
    void update();
    void draw();

    static Game* _instance;
    Game();
};

template<typename... Args>
void Game::log(const std::string& logStr, Args&&... args)
{
	_log.log(logStr, std::forward<Args>(args)...);
}
#endif
