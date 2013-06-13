#pragma once
#ifndef ENTITY_H
#define    ENTITY_H

#include <vector>
#include "../Graphics/IRender.hpp"
#include "../Graphics/Texture.hpp"
#include "../Utility/Vector.hpp"
#include "../Utility/Rect.hpp"

/* Entity class
 *
 *      Virtual base class of all ingame entities.
 *
 *      Entities should be added to gamestates via State::addEntity(Entity)
 *
 *      All derived classes contain a [Vectorf] position_ and a reference to a
 *      texture_ (loaded via [IRender]), as well as a [string] type_.
 *      visible_ determines whether the entity will be drawn
 *      Every [Entity] has a unique actorID_
 *      Every [Entity[ added to a [State] will automatically have its state_
 *      set accordingly.
 *
 *      Derived classes must override update, to define the entity's per-frame
 *      behaviour
 *
 *      Draw may be overridden, but should work as-is for all non-animated
 *      entities.
 *      To make an animation, see [Animation]
 *
 */

class State;

class Entity
{
public:
    //Game loop functions
    virtual void update() {}
    virtual void draw(IRender* const);

    std::vector<Entity*> collide(std::string type = "");

    /*!
     * \brief Returns the entity's z-layer
     */
    int getLayer() const
    {
        return layer_;
    }
    /*!
     * \brief Returns the entity's vector position
     */
    Vectorf const& getPos() const
    {
        return pos_;
    }
    /*!
     * \brief Returns the entity's hitbox
     * Returns the entity's hitbox in the format
     * (x-offset, y-offset, width, height) where the offse
     */
    Rect const& getHitBox() const
    {
        return hitbox_;
    }
    /*!
     * \brief Returns whether the entity is solid (deprecated)
     */
    bool isSolid() const
    {
        return solid_;
    }

    /*!
     * \brief Returns the entity's unique id
     */
    int getActorID() const
    {
        return actorID_;
    }
    /*!
     * \brief Returns the number of entities 
     */
    static int getNumEnts()
    {
        return numEnts_;
    }
    /*!
     * \brief Returns the entity's type
     */
    std::string getType() const
    {
        return type_;
    }

    /*!
     * \brief sets the entity's parent state
     *
     * Typically set by the state on addition. Don't change it unless you know
     * what you're doing.
     *
     * \param state A pointer to the parent state
     */
    void setState(State* const state);
    /*!
     * \brief sets the entity's position
     *
     * \param pos The entity's new position
     */
    void setPos(Vectorf const& pos);

    /* ------------------------------ *
     * Ctors/Dtor
     * ------------------------------ */
    Entity(Vectorf const& pos);
    virtual ~Entity();
    //Note: want shallow copy, default copy ctor works
protected:
    static int numEnts_;
    const  int actorID_;           //Unique ID

    //Member variables
    int                layer_;     //0
    Vectorf            pos_;
    Rect               hitbox_;    //(pos_.x,pos_.y,0,0)
    Texture     const* texture_;   //nullptr
    std::string        type_;      //""
    bool               solid_;     //false
    bool               visible_;   //true

    State*         state_;     //Set by parent State
};
#endif
