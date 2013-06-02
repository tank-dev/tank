#pragma once
#ifndef GAMESTATE_H
#define	GAMESTATE_H

#include <vector>
#include <memory>
#include <SDL/SDL_events.h>
#include "../Graphics/IRender.hpp"

class Entity;
class Game;

class GameState
{
public:
    void addEntity(Entity*);
    void removeEntity(Entity*);

    virtual bool initialize() = 0;
    virtual void handleEvents(SDL_KeyboardEvent* const) = 0;
    virtual void update();
    virtual void draw(IRender* const);

    GameState();
    virtual ~GameState();
protected:
    std::vector<Entity*> _entities;
    bool _initialized;
private:
    GameState(GameState const&);
    GameState& operator=(GameState const&);
};
#endif
