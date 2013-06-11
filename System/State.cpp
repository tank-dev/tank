#include "State.hpp"

#include "Entity.hpp"

State::State()
    : _initialized(false) { }

State::~State() { }

bool State::addEntity(Entity* entity)
{
	// Stops an entity being added several times
    for(auto existingEnt : _entities)
    {
        if(entity == existingEnt)
        {
            //TODO Log this in some way
            return false;
        }
    }

    entity->setState(this);
    _entities.push_back(entity);
	return true;
}

void State::removeEntity(Entity* const entity)
{
    //TODO Replace with algo
    for(unsigned int i = 0; i < _entities.size(); i++)
    {
        if(entity == _entities[i])
        {
            std::vector<Entity*>::iterator iter = _entities.begin()+i;
            delete(_entities[i]);
            _entities.erase(iter);
        }
    }
}

void State::update()
{
    for(auto entity : _entities)
    {
        entity->update();
    }
}

void State::draw(IRender* const render)
{
    for(auto entity : _entities)
    {
        entity->draw(render);
    }
}
