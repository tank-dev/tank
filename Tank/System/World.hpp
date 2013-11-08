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

#include "Camera.hpp"
#include "EventHandler.hpp"
#include "../Utility/Vector.hpp"
#include "../Utility/observing_ptr.hpp"

namespace tank {

class Entity;
class Game;

/*!
 * \brief Base class for game worlds ("Worlds")
 *
 * Handles Entity creation, destruction, rendering and updating. You can derive
 * from this class to add your own world-specific logic - it can also be useful
 * to handle world initialization in the constructor as opposed to from the
 * outside (e.g. in main).
 *
 * Worlds should be created via Game::makeWorld<T>(Args... args) for memory
 * safety. All worlds are stored within Game as a stack.
 *
 * All entities should be created using the similar method available from
 * World, makeEntity<T>(Args... args).
 *
 * \see Game
 * \see Entity
 * \see EventHandler
 */
class World
{
    bool updating_ {false};
    Camera camera_;
    std::vector<std::tuple<observing_ptr<World>, observing_ptr<Entity>>> toMove_;
    std::vector<std::unique_ptr<Entity>> newEntities_;
    std::vector<std::unique_ptr<EventHandler::Connection>> connections_;

public:
    EventHandler eventHandler;

    /*!
     * \brief Creates an Entity and adds it to the World
     *
     * Creates an Entity, setting its world pointer to point to it.
     * Adds a unique_ptr to the entity to the entity list.
     * Returns an observing_ptr<T> to the Entity created.
     *
     * \tparam T The type of Entity to construct
     * \param args the arguments to send to the entity's constructor
     * \return A raw pointer to the created Entity (NEVER DELETE IT)
     */
    template <typename T, typename... Args>
    observing_ptr<T> makeEntity(Args&&... args);

    /*!
     * \brief Inserts a unique_ptr to an Entity into the entity list
     *
     * This method provides a way to add entities that have
     * * been released from their original World via releaseEntity()
     * * been created independently of makeEntity()
     *
     * \param entity A unique_ptr to the Entity to be inserted
     * \see makeEntity()
     */
    void insertEntity(std::unique_ptr<Entity>&&);

    /*!
     * \brief Moves an Entity from one World to another
     *
     * This is essentially a shorthand for
     * world->insertEntity(this->releaseEntity(entity))
     *
     * \param world The World to which to move the Entity
     * \param entity A raw pointer to the Entity to be moved
     * \see insertEntity()
     * \see releaseEntity()
     */
    void moveEntity(observing_ptr<World>, observing_ptr<Entity>);

    /*!
     * \brief Removes an Entity from the entity list and returns a unique_ptr
     * to it
     *
     * \param entity A raw pointer to the Entity to be released
     * \see insertEntity()
     */
    std::unique_ptr<Entity> releaseEntity(observing_ptr<Entity>);

    /*
     * \brief Handle keyboard input on a per-frame basis (deprecated)
     *
     * When World is the active world, Game calls this once per frame, before
     * update() and draw().
     *
     * Override this to send keyboard input to entities that need it
     *
     * \param key SDL_KeyboardEvent representing the change in keyboard world
     * \see update()
     * \see draw()
     * \see Game
     */
    //virtual void handleEvents(sf::Keyboard::Key) {}

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

    Camera& camera()
    {
        return camera_;
    }

    /*!
     * \brief Get the list of entities
     *
     * \return A reference to the list of unique_ptrs to entities
     */
    virtual const std::vector<std::unique_ptr<Entity>>& getEntities()
    { return entities_; }

    World();
    virtual ~World();
    World(World const&) = delete;
    World& operator=(World const&) = delete;

    tank::observing_ptr<tank::EventHandler::Connection> connect(
            tank::EventHandler::Condition condition,
            tank::EventHandler::Effect effect);

protected:
    //TODO: Make private and add getter
    std::vector<std::unique_ptr<Entity>> entities_;

private:
    void addEntities();
    void moveEntities();
    void deleteEntities();
};

template <typename T, typename... Args>
observing_ptr<T> World::makeEntity(Args&&... args)
{
    static_assert(std::is_base_of<Entity, T>::value,
                  "Type must derive from Entity");

    std::unique_ptr<T> ent {new T(std::forward<Args>(args)...)};
    ent->setWorld(this);
    ent->onAdded();
    observing_ptr<T> ptr {ent};
    newEntities_.push_back(std::move(ent));
    return ptr;
}

}

#endif
