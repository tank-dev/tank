#include "Entity.hpp"

#include <cmath>
#include <algorithm>
#include "State.hpp"

int Entity::_numEnts = 0;

Entity::Entity(Vectorf const& pos)
    : _actorID(_numEnts++),
      _layer(0),
      _pos(pos),
      _hitbox({0}),
      _texture(nullptr),
      //_state (state),
      _type(""),
      _solid(false),
      _visible(true)
{
}

Entity::~Entity() {}

//Default draw function
void Entity::draw(IRender* const render)
{
    if(_texture)
    {
        render->draw(_texture, _pos);
    }
}

void Entity::setState(State* const state)
{
    _state = state;
}

void Entity::setPos(Vectorf const& pos)
{
    _pos = pos;
}

std::vector<Entity*> Entity::collide(std::string type)
{ 
    auto entList = _state->getEntities();
    std::vector<Entity*> collisions;

    if(type != "")
    {
        entList.erase(std::remove_if(entList.begin(), entList.end(),
                                     [type](Entity* ent)
        {
            return ent->getType() != type;
        }), entList.end());
    }

    for(auto ent : entList)
    {
        if(ent != this)
        {
            Rect const& A = _hitbox;
            Rect const& B = ent->getHitBox();

            double leftA   = A.x + _pos.x;
            double leftB   = B.x + ent->getPos().x;
            double rightA  = A.x + A.w + _pos.x;
            double rightB  = B.x + B.w + ent->getPos().x;
            double topA    = A.y + _pos.y;
            double topB    = B.y + ent->getPos().y;
            double bottomA = A.y + A.h + _pos.y;
            double bottomB = B.y + B.h + ent->getPos().y;

            if(leftA > rightB) continue;
            if(topA > bottomB) continue;
            if(rightA < leftB) continue;
            if(bottomA < topB) continue;

            collisions.push_back(ent);
        } 
    }

    return collisions;
}
