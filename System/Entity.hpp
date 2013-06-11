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
 *      All derived classes contain a [Vectorf] _position and a reference to a
 *      _texture (loaded via [IRender]), as well as a [string] _type.
 *      _visible determines whether the entity will be drawn
 *      Every [Entity] has a unique _actorID
 *      Every [Entity[ added to a [State] will automatically have its _state
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
        return _layer;
    }
    Vectorf const& getPos() const
    {
        return _pos;
    }
    Rect const& getHitBox() const
    {
        return _hitbox;
    }
    bool isSolid() const
    {
        return _solid;
    }

    int getActorID() const
    {
        return _actorID;
    }
    static int getNumEnts()
    {
        return _numEnts;
    }
    std::string getType() const
    {
        return _type;
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
    static int _numEnts;
    const  int _actorID;           //Unique ID

    //Member variables
    int                _layer;     //0
    Vectorf            _pos;
    Rect               _hitbox;    //(_pos.x,_pos.y,0,0)
    Texture     const* _texture;   //nullptr
    std::string        _type;      //""
    bool               _solid;     //false
    bool               _visible;   //true

    State*         _state;     //Set by parent State
};
#endif
