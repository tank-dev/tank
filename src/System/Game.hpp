#pragma once
#ifndef GAME_H
#define	GAME_H

#include <stack>
#include "IRender.hpp"
#include "GameState.hpp"
#include "Timer.hpp"
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

    GameState* state();
private:
    bool _initialized;
    bool _run;

    //Hacky hacky hacky
    bool _deleteState;

    IRender*   _render;

    GameState* _currentState;
    std::stack<GameState*> _states;
    Timer _frameTimer;

    void handleEvents();
    void update();
    void draw();

    static Game* _instance;
    Game();
};
#endif
