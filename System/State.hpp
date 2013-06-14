#pragma once
#ifndef GAMESTATE_H
#define    GAMESTATE_H

#include <vector>
#include <memory>
#include <SDL/SDL_events.h>
#include "../Graphics/IRender.hpp"

class Entity;
class Game;

/*!
 * \brief Base class for game states ("Worlds")
 *
 * Handles game logic 
 *
 * \see Entity
 * \see EventHandler
 */
class State
{
public:
	/*!
	 * \brief Adds an entity to the world, returns true if the entity is
	 * successfully added.
	 *
	 * \param Entity The entity to add.
	 * \return True if the entity is sucessfully added.
	 */
    template <typename T, typename... Args>
    T* makeEntity(Args&&... args)
    {
        static_assert(std::is_base_of<Entity,T>::value,
                      "Type must derive from Entity");

        T* ent = new T(std::forward<Args>(args)...);
        ent->setState(this);
        entities_.emplace_back(ent);
        return ent;
    }

    void insertEntity(std::unique_ptr<Entity>&&);
    void moveEntity(State*, Entity*);
    std::unique_ptr<Entity> releaseEntity(Entity*);
    void removeEntity(Entity*);

    virtual void handleEvents(SDL_KeyboardEvent* const) {}
    virtual void update();
    virtual void draw(IRender* const);

    virtual std::vector<std::unique_ptr<Entity>> const& getEntities() { return entities_; }

    State();
    virtual ~State();
protected:
    std::vector<std::unique_ptr<Entity>> entities_;
private:
    State(State const&);
    State& operator=(State const&);
};
#endif
