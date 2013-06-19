#pragma once
#ifndef ENTITY_H
#define    ENTITY_H

#include <vector>
#include "../Graphics/Texture.hpp"
#include "../Utility/Vector.hpp"
#include "../Utility/Rect.hpp"


class State;

/*!
 * \brief Base class for all in-game entities.
 *
 * Entities should be added to gamestates via State::addEntity(Entity)
 *
 * All derived classes contain a Vectorf position and a reference to a
 * texture (loaded via IRender), as well as a string type.
 * visible determines whether the entity will be drawn
 * Every Entity has a unique actorID
 * Every Entity added to a State will automatically have its state
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
public:
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
    virtual void draw();

    /*!
     * \brief Check for collisions with the entity (deprecated?)
     *
     * Render the entity for the current frame
     * \param type The type of entity with which to detect collisions (defaults
     * to all)
     * \return A list of all colliding entitities of type.
     * \see setType()
     */
    std::vector<Entity*> collide(std::string type = "");

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
     * \brief Returns the entity's vector position
     *
     * \return Entity's position
     */
    Vectorf const& getPos() const
    {
        return pos_;
    }
    /*!
     * \brief Returns the entity's hitbox
     *
     * Returns the entity's hitbox in the format
     * (x-offset, y-offset, width, height) where the offse
     * \return Entity's hitbox
     */
    Rect const& getHitBox() const
    {
        return hitbox_;
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
     * \brief Returns the entity's type
     *
     * \return The entity's type
     */
    std::string getType() const
    {
        return type_;
    }

    /*!
     * \brief Sets the entity's parent state
     *
     * Typically set by the state on addition. Don't change it unless you know
     * what you're doing.
     *
     * \param state A pointer to the parent state
     */
    void setState(State* const state);
    /*!
     * \brief Sets the entity's position
     *
     * \param pos The position to which to move
     */
    void setPos(Vectorf const& pos);

    /*!
     * \brief Sets the entity's type
     *
     * \param type The new type
     */
    void setType(std::string type) { type_ = type; }

    /*!
     * \brief Constructs an entity at position pos
     *
     * \param pos The position of the entity
     */
    Entity(Vectorf const& pos);
    virtual ~Entity();
protected:
    static int numEnts_;    //(NOT SET)
    const  int actorID_;    //Unique ID (NOT SET)

    //Member variables
    int         layer_;     //0
    Vectorf     pos_; 
    Rect        hitbox_;    //(0,0,0,0)
    std::string type_;      //""
    bool        solid_;     //false
    bool        visible_;   //true

    Texture const* texture_;//nullptr
    State* state_;          //Set by parent State
};
#endif
