#include "State.hpp"

#include "Entity.hpp"
#include "Game.hpp"

State::State() {}

State::~State() { }

void State::insertEntity(std::unique_ptr<Entity>&& entity)
{
	if (!entity.get())
	{
        Game::log << "Warning: You can't add a null entity." << std::endl;
		return;
	}
	// Stops an entity being added several times
    //TODO replace with algo
    for(auto& existingEnt : entities_)
    {
        if(entity.get() == existingEnt.get())
        {
            //Maybe shouldn't warn here
            Game::log << "Warning: Entity already added" << std::endl;

            return;
        }
    }

    entity->setState(this);
    entities_.push_back(std::move(entity));
}

void State::moveEntity(State* state, Entity* entity)
{
	if (!entity)
	{
        Game::log << "Warning: You can't move null entity." << std::endl;
		return;
	}
	// Stops an entity being added several times
    //TODO replace with algo
    std::unique_ptr<Entity> entPtr = releaseEntity(entity);
    if(!entPtr.get())
    {
        Game::log << "Entity not found in move operation" << std::endl;
        return;
    }

    state->insertEntity(std::move(entPtr));
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
            Game::log << "Deleting" << std::endl;
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

void State::draw()
{
    for(auto& entity : entities_)
    {
        entity->draw();
    }
}
