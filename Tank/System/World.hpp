// Copyright (©) Jamie Bayne, David Truby, David Watson 2013-2014.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt)

#ifndef TANK_GAMESTATE_HPP
#define TANK_GAMESTATE_HPP

#include <vector>
#include <tuple>
#include <memory>

#include "Camera.hpp"
#include "EventHandler.hpp"
#include "../Utility/Vector.hpp"
#include "../Utility/observing_ptr.hpp"

namespace tank
{

class Entity;
class Game;

/*!
 * \brief Class for managing entities, encapsulating game states.
 *
 * Worlds handle Entity creation, destruction, rendering and updating. Often
 * each class deriving World will represent a different state of the game, *e.g.*
 * Menu, Main, Paused.
 *
 * You should derive from this class to add your own world-specific logic - it
 * is also advised to handle world initialization in World() as opposed
 * to externally (e.g. in main).
 *
 * A World should be created via Game::makeWorld<WorldType>(), which
 * constructs it, adds it to the top of the World stack, and returns an
 * observing_ptr to it.
 *
 * All entities should be created using the similar method available on
 * World instances, World.makeEntity<EntityType>().
 *
 * \see Game
 * \see Entity
 * \see EventHandler
 */
class World
{
    bool updating_ {false};
    Camera camera_;
    std::vector<std::tuple<observing_ptr<World>, observing_ptr<Entity>>>
            toMove_;
    std::vector<std::unique_ptr<Entity>> newEntities_;
    std::vector<std::unique_ptr<EventHandler::Connection>> connections_;
    EventHandler eventHandler_;

public:
    /*! \brief Returns a reference to the world's unique EventHandler */
    EventHandler& eventHandler()
    {
        return eventHandler_;
    }

    /*!
     * \brief Creates an Entity to be added to the world at the beginning of the
     * next frame.
     *
     * This is a factory function which creates an instance of a class deriving
     * from Entity. The entity is constructed immediately, passing the `args`
     * provided. The entity's world pointer is then set, and Entity.onAdded()
     * is called. At the beginning of the next frame, the entity is added to the
     * entity list.
     *
     * Example code:
     *
     * ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~{.cpp}
     *     class MyEnt : public tank::Entity
     *     {
     *     public:
     *         MyEnt(tank::Vectorf pos, int a) : tank::Entity(pos) {}
     *     };
     *
     *     auto myWorld = Game::makeWorld();
     *     myWorld->makeEntity<MyEnt>(tank::Vectorf {20, 30}, 2);
     * ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
     *
     * \tparam T The type of entity to create.
     * \param args Arguments to pass to T's constructor.
     * \return An observing_ptr of type T to the newly created World
     */
    template <typename T, typename... Args>
    observing_ptr<T> makeEntity(Args&&... args);

    /*!
     * \brief Inserts an Entity into the entity list
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
     * \brief Moves an Entity from one world to another
     *
     * This is essentially a shorthand for
     * world->insertEntity(this->releaseEntity(entity))
     *
     * \param world The world to which to move the entity
     * \param entity A raw pointer to the entity to be moved
     * \see insertEntity()
     * \see releaseEntity()
     */
    void moveEntity(observing_ptr<World>, observing_ptr<Entity>);

    /*!
     * \brief Removes an Entity from the entity list and returns it
     *
     * \param entity An observing_ptr pointer to the entity to be released
     * \see insertEntity()
     */
    std::unique_ptr<Entity> releaseEntity(observing_ptr<Entity>);

    /*!
     * \brief Update all Entity instances in the entity list
     *
     * Game calls this on the current world once per frame, before calling draw().
     *
     * Override this to add frame logic specific to the world, but be sure to
     * update the entity list by calling World.update().
     *
     * \see draw()
     * \see Game
     */
    virtual void update();

    /*!
     * \brief Draw all Entity instances in the entity list
     *
     * When world is the active World, the game loop calls this once per
     * iteration, after update().
     *
     * By default, it will sort the entity list by Entity.getLayer() before
     * drawing.
     *
     * Override this to specify new behaviour when drawing the entire world each
     * frame, *e.g.* to sort the entity list some other way, but be sure to then
     * draw all entities by either calling
     * World.draw() or looping over the entities list:
     *
     * ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~{.cpp}
     * for (auto& e : entities_) {
     *     e->draw(camera());
     * }
     * ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
     *
     * \see update()
     * \see Game
     */
    virtual void draw();

    /*! \brief Returns a reference to the world's Camera */
    Camera& camera()
    {
        return camera_;
    }

    // TODO: This function is really unclear. Will have a further look later
    Vectorf worldFromScreenCoords(Vectorf const& screenCoords)
    {
        return camera().worldFromScreenCoords(screenCoords);
    }

    /*!
     * \brief Returns the entity list
     *
     * \return A reference to the list of unique_ptrs to entities
     */
    virtual const std::vector<std::unique_ptr<Entity>>& getEntities()
    {
        return entities_;
    }

    //TODO Finish documentation
    /*!
     * In derived classes, the constructor is where you should create and load
     * resources such as music, graphics and entities specific to the world.
     */
    World() = default;
    virtual ~World();
    World(World const&) = delete;
    World& operator=(World const&) = delete;

    /*!
     * \brief Helper function to create and store EventHandler connections for
     * the world.
     *
     * Equivalent to a call to EventHandler.connect() on the world's
     * EventHandler, except the returned EventHandler::Connection is stored
     * in a list data member of the world, and an observing_ptr to
     * it is returned instead.
     *
     * This should be used for registering events with lifetimes equal to the
     * world's, and is not suitable for Entity specific events -- see
     * Entity.connect() instead.
     *
     * \see EventHandler
     */
    tank::observing_ptr<tank::EventHandler::Connection>
            connect(tank::EventHandler::Condition condition,
                    tank::EventHandler::Effect effect);

protected:
    /*! \brief list of Entity instances in the World */
    // TODO: Make private and add getter
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
    static_assert(std::is_convertible<T*, Entity*>::value,
                  "Type must derive publically from Entity");

    std::unique_ptr<T> ent{new T(std::forward<Args>(args)...)};
    ent->setWorld(this);
    ent->onAdded();
    observing_ptr<T> ptr{ent};
    newEntities_.push_back(std::move(ent));
    return ptr;
}
}

#endif
