#pragma once
#ifndef GAME_H
#define	GAME_H

#include <stack>
#include <memory>
#include "../Graphics/IRender.hpp"
#include "../System/IWindow.hpp"
#include "../Utility/Timer.hpp"
#include "GameState.hpp"
#include <SDL/SDL_events.h>

class Game
{
public:
    static Game* Instance();
    ~Game();

    bool initialize();
    void run();

    bool addState(GameState*);
    void popState();

    GameState& state();
private:
    bool _initialized;
    bool _run;

    //Hacky hacky hacky
    bool _popState;

    IWindow* _window;
    IRender* _render;

    std::stack<std::unique_ptr<GameState>> _states;
    Timer _frameTimer;

    void handleEvents();
    void update();
    void draw();

    static Game* _instance;
    Game();
};
#endif
