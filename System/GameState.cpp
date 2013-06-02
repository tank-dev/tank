#include "GameState.hpp"

#include <iostream>
#include "Entity.hpp"

GameState::GameState()
    : _initialized(false) { }

GameState::~GameState() { }

void GameState::addEntity(Entity* entity)
{
    for(auto existingEnt : _entities)
    {
        if(entity == existingEnt)
        {
            std::cout<< "Entity already added." << std::endl;
            return;
        }
    }

    entity->setState(this);
    _entities.push_back(entity);
}

void GameState::removeEntity(Entity* const entity)
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

void GameState::update()
{
    for(auto entity : _entities)
    {
        entity->update();
    }
}

void GameState::draw(IRender* const render)
{
    for(auto entity : _entities)
    {
        entity->draw(render);
    }
}
