#include "Entity.hpp"

#include <cmath>
#include "GameState.hpp"

int Entity::_numEnts = 0;

Entity::Entity(Vector const& pos)
    : _actorID(_numEnts++),
      _layer(0),
      _pos(pos),
    _hitBox({ static_cast<int>(round(_pos.x)),
            static_cast<int>(round(_pos.y))
}),
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

void Entity::setState(GameState* const state)
{
    _state = state;
}

void Entity::setPos(Vector const& pos)
{
    Vector dif = pos -_pos;
    _pos += dif;
    _hitBox.x += dif.x;
    _hitBox.y += dif.y;
}