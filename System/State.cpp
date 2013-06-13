#include "State.hpp"

#include "Entity.hpp"
#include "Game.hpp"

State::State()
    : initialized_(false) { }

State::~State() { }

void State::insertEntity(std::unique_ptr<Entity>&& entity)
{
	if (!entity.get())
	{
        Game::Instance()->log() << "Warning: You can't add a null entity.";
		return;
	}
	// Stops an entity being added several times
    //TODO replace with algo
    for(auto& existingEnt : entities_)
    {
        if(entity.get() == existingEnt.get())
        {
            //Maybe shouldn't warn here
            Game::Instance()->log() << "Warning: Entity already added";

            return;
        }
    }

    entity->setState(this);
    entities_.push_back(std::move(entity));
}

std::unique_ptr<Entity> State::releaseEntity(Entity* entity)
{
    std::unique_ptr<Entity> ptr;
    //TODO Replace with algo
    for(unsigned int i = 0; i < entities_.size(); i++)
    {
        if(entity == entities_[i].get())
        {
            const auto iter = entities_.begin()+i;
            ptr = std::move(entities_[i]);
            entities_.erase(iter);
        }
    }

    return ptr;
}

void State::removeEntity(Entity* entity)
{
    //TODO Replace with algo
    for(unsigned int i = 0; i < entities_.size(); i++)
    {
        if(entity == entities_[i].get())
        {
            const auto iter = entities_.begin()+i;
            entities_.erase(iter);
        }
    }
}

void State::update()
{
    for(auto& entity : entities_)
    {
        entity->update();
    }
}

void State::draw(IRender* const render)
{
    for(auto& entity : entities_)
    {
        entity->draw(render);
    }
}
