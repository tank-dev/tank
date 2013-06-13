#include "State.hpp"

#include "Entity.hpp"
#include "Game.hpp"

State::State()
    : initialized_(false) { }

State::~State() { }

bool State::addEntity(Entity* entity)
{
	if (!entity)
	{
        Game::Instance()->log() << "Warning: You can't add a null entity.";
		return false;
	}
	// Stops an entity being added several times
    for(auto existingEnt : entities_)
    {
        if(entity == existingEnt)
        {
            Game::Instance()->log() << "Warning: Entity already added";

            return false;
        }
    }

    entity->setState(this);
    entities_.push_back(entity);
	return true;
}

void State::removeEntity(Entity* const entity)
{
    //TODO Replace with algo
    for(unsigned int i = 0; i < entities_.size(); i++)
    {
        if(entity == entities_[i])
        {
            std::vector<Entity*>::iterator iter = entities_.begin()+i;
            delete(entities_[i]);
            entities_.erase(iter);
        }
    }
}

void State::update()
{
    for(auto entity : entities_)
    {
        entity->update();
    }
}

void State::draw(IRender* const render)
{
    for(auto entity : entities_)
    {
        entity->draw(render);
    }
}
