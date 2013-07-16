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

#ifndef TANK_GAMESTATE_HPP
#define TANK_GAMESTATE_HPP

#include <vector>
#include <tuple>
#include <memory>
#include <SFML/Window/Event.hpp>
#include <SFML/Window/Keyboard.hpp>

#include "../Utility/Vector.hpp"
#include "Entity.hpp"

namespace tank {

class Game;

/*!
 * \brief Base class for game states ("Worlds")
 *
 * Handles Entity creation, destruction, rendering and updating. You can derive
 * from this class to add your own state-specific logic - it can also be useful
 * to handle state initialization in the constructor as opposed to from the
 * outside (e.g. in main).
 *
 * States should be created via Game::makeState<T>(Args... args) for memory
 * safety. All states are stored within Game as a stack.
 *
 * All entities should be created using the similar method available from
 * State, makeEntity<T>(Args... args).
 *
 * \see Game
 * \see Entity
 * \see EventHandler
 */
class State
{
public:
    /*!
     * \brief Creates an Entity and adds it to the State
     *
     * Creates an Entity, setting its state pointer to point to it.
     * Adds a shared_ptr to the entity to the entity list.
     * Returns a raw pointer of type T* to the Entity created.
     *
     * \tparam T The type of Entity to construct
     * \param args the arguments to send to the entity's constructor
     * \return A raw pointer to the created Entity (NEVER DELETE IT)
     */
    template <typename T, typename... Args>
    std::shared_ptr<T> makeEntity(Args&&... args);

    /*!
     * \brief Inserts a shared_ptr to an Entity into the entity list
     *
     * This method provides a way to add entities that have
     * * been released from their original State via releaseEntity()
     * * been created independently of makeEntity()
     *
     * \param entity A shared_ptr to the Entity to be inserted
     * \see makeEntity()
     */
    void insertEntity(std::shared_ptr<Entity> entity);

    /*!
     * \brief Moves an Entity from one State to another
     *
     * This is essentially a shorthand for
     * state->insertEntity(this->releaseEntity(entity))
     *
     * \param state The State to which to move the Entity
     * \param entity A raw pointer to the Entity to be moved
     * \see insertEntity()
     * \see releaseEntity()
     */
    void moveEntity(State*, std::shared_ptr<Entity>);

    /*!
     * \brief Removes an Entity from the entity list and returns a shared_ptr
     * to it
     *
     * \param entity A raw pointer to the Entity to be released
     * \see insertEntity()
     */
    std::shared_ptr<Entity> releaseEntity(std::shared_ptr<Entity>);

    /*!
     * \brief Handle keyboard input on a per-frame basis (deprecated)
     *
     * When State is the active state, Game calls this once per frame, before
     * update() and draw().
     *
     * Override this to send keyboard input to entities that need it
     *
     * \param key SDL_KeyboardEvent representing the change in keyboard state
     * \see update()
     * \see draw()
     * \see Game
     */
    virtual void handleEvents(sf::Keyboard::Key) {}

    /*!
     * \brief Update all entities in the state's entities list
     *
     * When State is the active state, Game calls this once per frame, between
     * handleEvents() and draw()
     *
     * Override this to specify new logic for updates, but be sure to update the
     * entity list, either by looping over and calling update, or by calling
     * State::update()
     *
     * \see handleEvents()
     * \see draw()
     * \see Game
     */
    virtual void update();

    /*!
     * \brief Draw all entities in the state's entities list
     *
     * When State is the active state, Game calls this once per frame, after
     * handleEvents() and update()
     *
     * Override this to specify new drawing operations, or to sort the entities
     * list before drawing, but be sure to then draw all entities by either
     * looping over the entities list or calling State::draw()
     *
     * \param render The render context to draw to
     *
     * \see handleEvents()
     * \see update()
     * \see Game
     */
    virtual void draw();

    virtual Vectorf getCamera() const
    {
        return camera_;
    }
    virtual void setCamera(Vectorf camera)
    {
        camera_ = camera;
    }

    /*!
     * \brief Get the list of entities
     *
     * \return A reference to the list of shared_ptrs to entities
     */
    virtual const std::vector<std::shared_ptr<Entity>>& getEntities()
    { return entities_; }

    State();
    virtual ~State();
protected:
    //TODO: Make private and add getter
    std::vector<std::shared_ptr<Entity>> entities_;
private:
    Vectorf camera_;
    std::vector<std::tuple<State*, std::shared_ptr<Entity>>> toMove_;
    bool updating_;

    void moveEntities();
    void deleteEntities();

    State(State const&);
    State& operator=(State const&);
};

template <typename T, typename... Args>
std::shared_ptr<T> State::makeEntity(Args&&... args)
{
    static_assert(std::is_base_of<Entity, T>::value,
                  "Type must derive from Entity");

    auto ent = std::make_shared<T>(std::forward<Args>(args)...);
    ent->setState(this);
    ent->onAdded();
    entities_.push_back(ent);
    return ent;
}

}

#endif
