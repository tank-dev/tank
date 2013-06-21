#include "State.hpp"

#include <algorithm>
#include "Entity.hpp"
#include "Game.hpp"

namespace tank {

State::State() {}

State::~State() { }

void State::insertEntity(std::unique_ptr<Entity>&& entity)
{
    if (not entity.get())
	{
        Game::log << "Warning: You can't add a null entity." << std::endl;
		return;
	}
	// Stops an entity being added several times

    auto x = find_if(begin(entities_), end(entities_),
                     [&entity](std::unique_ptr<Entity>& existing) {
            return entity.get() == existing.get();
    });
    if (x != end(entities_)) {
        throw std::invalid_argument("Entity already added");
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
    auto it = std::find_if(begin(entities_), end(entities_), [&entity](std::unique_ptr<Entity>& ent) {
        return entity == ent.get();
    });

    auto ptr = std::move(*it);
    entities_.erase(it);
    return ptr;
}

/*
void State::removeEntity(Entity* entity)
{
    // Get the unique_ptr from releaseEntity
    auto x = releaseEntity(entity);
    // AND THROW IT AWAY! :D
    *x;
}*/

void State::update()
{
    for(auto& entity : entities_)
    {
        entity->update();
    }
    entities_.erase(std::remove_if(begin(entities_), end(entities_), [](const std::unique_ptr<Entity>& ent) {
                        return ent->isRemoved();
    }), end(entities_));
}

void State::draw()
{
    for(auto& entity : entities_)
    {
        entity->draw();
    }
}

}
