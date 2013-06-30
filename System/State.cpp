/* This file is part of Tank.
 *
 * Tank is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Lesser General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * Tank is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License and
 * the GNU Lesser General Public Licence along with Tank. If not, see
 * <http://www.gnu.org/licenses/>.
 *
 * Copyright 2013 (©) Jamie Bayne, David Truby, David Watson.
 */

#include "State.hpp"

#include <algorithm>
#include "Entity.hpp"
#include "Game.hpp"

namespace tank
{

State::State() {}

State::~State() {}

void State::insertEntity(std::unique_ptr<Entity>&& entity)
{
    if (not entity.get())
    {
        Game::log << "Warning: You can't add a null entity." << std::endl;
        return;
    }
    // Stops an entity being added several times

    auto x = find_if(begin(entities_), end(entities_),
                     [&entity](std::unique_ptr<Entity>& existing)
    {
            return entity.get() == existing.get();
    });

    if (x != end(entities_))
    {
        throw std::invalid_argument("Entity already added");
    }

    entity->onAdded();
    entity->setState(this);
    entities_.push_back(std::move(entity));
}

void State::moveEntity(State* state, Entity* entity)
{
    if (not entity)
    {
        Game::log << "Warning: You can't move null entity." << std::endl;
        return;
    }

    std::unique_ptr<Entity> entPtr = releaseEntity(entity);
    if (not entPtr.get())
    {
        Game::log << "Entity not found in move operation" << std::endl;
        return;
    }

    state->insertEntity(std::move(entPtr));
}

std::unique_ptr<Entity> State::releaseEntity(Entity* entity)
{
    auto it = std::find_if(begin(entities_), end(entities_),
                           [&entity](std::unique_ptr<Entity>& ent)
    {
        return entity == ent.get();
    });

    if (it == end(entities_))
    {
        return nullptr;
    }

    auto ent = std::move(*it);
    entities_.erase(it);
    ent->onRemoved();
    return ent;
}

void State::update()
{
    for (auto& entity : entities_)
    {
        entity->update();
    }
    entities_.erase(std::remove_if(begin(entities_), end(entities_),
                                   [](const std::unique_ptr<Entity>& ent)
    {
                        return ent->isRemoved();
    }), end(entities_));
}

void State::draw()
{
    for (auto& entity : entities_)
    {
        entity->draw();
    }
}

}
