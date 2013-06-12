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

    /* ------------------------------ *
     * Getters
     * ------------------------------ */
    int getLayer() const
    {
        return layer_;
    }
    Vectorf const& getPos() const
    {
        return pos_;
    }
    Rect const& getHitBox() const
    {
        return hitbox_;
    }
    bool isSolid() const
    {
        return solid_;
    }

    int getActorID() const
    {
        return actorID_;
    }
    static int getNumEnts()
    {
        return numEnts_;
    }
    std::string getType() const
    {
        return type_;
    }

    /* ------------------------------ *
     * Setters
     * ------------------------------ */
    void setState(State* const state);
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
