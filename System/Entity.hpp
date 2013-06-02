#pragma once
#ifndef ENTITY_H
#define	ENTITY_H

//{{{Includes
#include "../Graphics/IRender.hpp"
#include "../Graphics/Texture.hpp"
#include "../Utility/Vector.hpp"
#include "../Utility/Rect.hpp"
//}}}

/* Entity class
 *
 * {{{Description:
 *
 *      Virtual base class of all ingame entities.
 *
 *      Entities should be added to gamestates via GameState::addEntity(Entity)
 *
 *      All derived classes contain a [Vector] _position and a reference to a
 *      _texture (loaded via [IRender]), as well as a [string] _type.
 *      _visible determines whether the entity will be drawn
 *      Every [Entity] has a unique _actorID
 *      Every [Entity[ added to a [GameState] will automatically have its _state
 *      set accordingly.
 *
 *      Derived classes must override update, to define the entitiy's per-frame
 *      behaviour
 *
 *      Draw may be overridden, but should work as-is for all non-animated
 *      entities.
 *      To make an animation, see [Animation]
 *
 * }}}
 *
 */

class GameState;

class Entity
{
public:
    //Game loop functions
    virtual void update() = 0;
    virtual void draw(IRender* const);

    //TODO Replace with FP-style collide( "type" )
    virtual void isInside(Entity*) = 0;

    //{{{Getters
    int                getLayer()   const
    {
        return _layer;
    }
    Vector      const& getPos()     const
    {
        return _pos;
    }
    Rect        const& getHitBox()  const
    {
        return _hitBox;
    }
    bool               isSolid()    const
    {
        return _solid;
    }

    int                getActorID() const
    {
        return _actorID;
    }
    static int         getNumEnts()
    {
        return _numEnts;
    }
    std::string const& getType()    const
    {
        return _type;
    }
    //}}}

    //{{{Setters
    void setState(GameState* const  state);
    void setPos(Vector     const& pos);
    //}}}

    /* ------------------------------ *
     * Constructor and Destructor
     * ------------------------------ */
    Entity(Vector const& pos);
    virtual ~Entity();
    //Note: WANT shallow copy, default copy ctor works
protected:
    static int _numEnts;
    const  int _actorID;           //Unique ID

    //{{{Member variables
    //DEFAULT VALUE
    int                _layer;     //0
    Vector             _pos;
    Rect               _hitBox;    //(_pos.x,_pos.y,0,0)
    Texture     const* _texture;   //NULL
    std::string        _type;      //""
    bool               _solid;     //false
    bool               _visible;   //true

    GameState*         _state;     //Set by parent GameState
    //}}}
};
#endif
