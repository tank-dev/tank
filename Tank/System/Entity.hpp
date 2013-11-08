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

#ifndef TANK_ENTITY_HPP
#define TANK_ENTITY_HPP

#include <vector>
#include <string>
#include <memory>
#include "../Graphics/Graphic.hpp"
#include "../Graphics/Image.hpp"
#include "../Utility/observing_ptr.hpp"
#include "../Utility/Rect.hpp"
#include "../Utility/Vector.hpp"
#include "Camera.hpp"
#include "EventHandler.hpp"
#include "Game.hpp"

namespace tank
{

class World;

/*!
 * \brief Base class for all in-game entities.
 *
 * Entities should be added to worlds via World::addEntity(Entity)
 *
 * All derived classes contain a Vectorf position and a reference to a
 * texture (loaded via IRender), as well as a string type.
 * visible determines whether the entity will be drawn
 * Every Entity has a unique actorID
 * Every Entity added to a World will automatically have its world
 * set accordingly.
 *
 * Derived classes must override update, to define the entity's per-frame
 * behaviour
 *
 * Draw may be overridden, but should work as-is for all non-animated
 * entities.
 * \see Animation
 * \see IRender
 */
class Entity
{
    Vectorf pos_;
    float rot_ {};
    Rectd hitbox_ {};
    bool solid_ {false};
    int layer_ {};
    bool removed_ {false};
    observing_ptr<World> world_ {nullptr}; //Set by parent World

    std::vector<std::string> types_;
    std::vector<std::unique_ptr<Graphic>> graphics_;
    std::vector<std::unique_ptr<EventHandler::Connection>> connections_;

    static int numEnts_;
    const  int actorID_;

public:
    /*!
     * \brief Constructs an entity at position pos
     *
     * \param pos The position of the entity
     */
    Entity(Vectorf pos = {0,0});
    /*!
     * \brief Run entity's per-frame game logic
     */

    virtual void update() {}

    /*!
     * \brief Render the entity
     *
     * Render the entity for the current frame
     * \param render The Render instance with which to render the entity
     */
    virtual void draw(Camera const&);

    /*!
     * \brief Check for collisions with the entity (deprecated?)
     *
     * Render the entity for the current frame
     * \param type The type of entity with which to detect collisions (defaults
     * to all)
     * \return A list of all colliding entitities of type.
     * \see setType()
     */
    std::vector<observing_ptr<Entity>> collide(std::vector<std::string> types = {});

    /*!
     * \brief Returns the entity's vector position
     *
     * \return Entity's position
     */
    Vectorf const& getPos() const
    {
        return pos_;
    }

    /*!
     * \brief Returns the entity's rotation
     *
     * \return Entity's rotation in degrees
     */
    float getRotation() const
    {
        return rot_;
    }

    /*!
     * \brief Returns the entity's hitbox
     *
     * Returns the entity's hitbox in the format
     * (x-offset, y-offset, width, height), the offset being a translation to
     * the bottom right from the entity's position vector.
     *
     * \return Entity's hitbox
     */
    Rectd const& getHitbox() const
    {
        return hitbox_;
    }

    /*!
     * \brief Returns the entity's types
     *
     * \return A list of the entity's types
     */
    std::vector<std::string> const& getTypes() const
    {
        return types_;
    }

    bool isType(std::string type)
    {
        return std::find(types_.begin(), types_.end(), type) != types_.end();
    }


    /*!
     * \brief Returns whether the entity is solid (deprecated)
     *
     * \return Whether or not the entity is solid
     */
    bool isSolid() const
    {
        return solid_;
    }

    /*!
     * \brief Returns the entity's z-layer
     *
     * \return Entity's z-layer
     */
    int getLayer() const
    {
        return layer_;
    }

    /*!
     * \brief Returns a Graphic from the Entity's graphic list
     *
     * \return unique_ptr to Graphic at specified position in graphic list
     */
    std::unique_ptr<Graphic> const& getGraphic(unsigned int i = 0) const;

    /*!
     * \brief Returns an Entity's graphic list
     *
     * \return Const reference to Entity's graphic list
     */
    std::vector<std::unique_ptr<Graphic>> const& getGraphicList()
    {
        return graphics_;
    }

    /*!
     * \brief Returns a pointer to the entity's parent World
     *
     * \return Entity's parent world
     */
    observing_ptr<World> getWorld() const
    {
        if (world_ == nullptr)
        {
            throw std::runtime_error (
                    "Entity World pointer is null (try Entity::onAdded)");
        }
        return world_;
    }

    /*!
     * \brief Returns the entity's unique id (deprecated)
     *
     * \return Entity ID
     */
    int getActorID() const
    {
        return actorID_;
    }

    /*!
     * \brief Returns the number of entities (deprecated)
     *
     * \return The number of entities that have been constructed
     */
    static int getNumEnts()
    {
        return numEnts_;
    }

    /*!
     * \brief Sets the entity's position
     *
     * \param pos The position to which to move
     */
    virtual void setPos(Vectorf pos);

    /*!
     * \brief Moves the entity pixel by pixel while cond is false
     *
     * \param displacement Vectorial distance to move entity
     * \param cond Condition to stop movement (e.g. not collide("solid").empty())
     *
     * \return True if moved full displacement, false otherwise
     */
    virtual bool moveBy(Vectorf displacement, std::function<bool()> cond);

    virtual void moveBy(Vectorf displacement);

    /*!
     * \brief Sets the entity's rotation
     *
     * \param pos The entity's new rotation in degrees
     */
    virtual void setRotation(float rot);

    /*!
     * \brief Sets the entity's hitbox
     *
     * \param hitbox The new hitbox
     */
    virtual void setHitbox(Rectd hitbox);

    /*!
     * \brief Sets entity's type for collision detection (removing all other
     * types)
     *
     * \param type The type to add
     */
    void setType(std::string type);

    /*!
     * \brief Adds a type to the entity for collision detection, etc.
     *
     * \param type The type to add
     */
    void addType(std::string type);

    /*!
     * \brief Sets the entity's solidity (deprecated)
     *
     * \param solid Whether the entity should be solid or not
     */
    void setSolid(bool solid);

    /*!
     * \brief Sets the entity's z-layer
     *
     * \param layer The new layer
     */
    void setLayer(int layer);

    /*!
     * \brief Create a Graphic and Add it to the Entity's graphic list
     *
     * \tparam T Type of Graphic to create
     * \tparam Args Arguments to send to T's constructor
     * \param args The arguments to T's constructor
     * \return A pointer of type T to the created Graphic
     */
    template <typename T = tank::Image, typename... Args>
    observing_ptr<T> makeGraphic(Args&&... args);

    /*!
     * \brief Sets the entity's parent world
     *
     * Typically set by the world on addition. Don't call it unless you know
     * what you're doing.
     *
     * \param world A pointer to the parent world
     */
    void setWorld(const observing_ptr<World> world);

    /*!
     * \brief Remove the entity from the world.
     */
    void remove() { removed_ = true; }

    /*!
     * \return if the entity has been removed.
     */
    bool isRemoved() { return removed_; }

    /*!
     * \brief Called when the entitiy is added to a World
     */
    virtual void onAdded() {}

    /*!
     * \brief Called when the entity is removed from a World
     */
    virtual void onRemoved() {}

    virtual bool offScreen() const;

    static std::function<bool()> offScreen(const tank::observing_ptr<Entity> e)
    {
        return [e]{return e->offScreen();};
    }

    virtual ~Entity();

    tank::observing_ptr<tank::EventHandler::Connection> connect(
            tank::EventHandler::Condition condition,
            tank::EventHandler::Effect effect);
};

template <typename T, typename... Args>
observing_ptr<T> Entity::makeGraphic(Args&&... args)
{
    static_assert(std::is_base_of<Graphic,T>::value,
                  "Type must derive from Graphic");

    std::unique_ptr<T> g {new T(std::forward<Args>(args)...)};
    observing_ptr<T> ptr {g};

    // If no hitbox, set to image bounds
    if (getHitbox() == Rectd() and getGraphicList().empty())
    {
        auto hb = g->getSize();
        setHitbox(Rectd(0, 0, hb.x, hb.y));
    }

    graphics_.push_back(std::move(g));
    return ptr;
}

using EntityPtr = tank::observing_ptr<Entity>;

}
#endif
