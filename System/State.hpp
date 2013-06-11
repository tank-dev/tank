#pragma once
#ifndef GAMESTATE_H
#define    GAMESTATE_H

#include <vector>
#include <memory>
#include <SDL/SDL_events.h>
#include "../Graphics/IRender.hpp"

class Entity;
class Game;

class State
{
public:
	/**
	 * @brief Adds an entity to the world, returns true if the entity is
	 * successfully added.
	 *
	 * @param Entity The entity to add.
	 *
	 * @return True if the entity is sucessfully added.
	 */
    bool addEntity(Entity*);
    void removeEntity(Entity*);

    virtual bool initialize() = 0;
    virtual void handleEvents(SDL_KeyboardEvent* const) = 0;
    virtual void update();
    virtual void draw(IRender* const);

    virtual std::vector<Entity*>& getEntities() { return _entities; }

    State();
    virtual ~State();
protected:
    std::vector<Entity*> _entities;
    bool _initialized;
private:
    State(State const&);
    State& operator=(State const&);
};
#endif
