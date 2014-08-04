// Copyright (©) Jamie Bayne, David Truby, David Watson 2013-2014.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt)

#include "World.hpp"

#include <algorithm>
#include <stdexcept>

#include <boost/range/algorithm.hpp>
#include <boost/range/algorithm_ext.hpp>

#include "Entity.hpp"
#include "Game.hpp"

namespace tank
{

World::~World()
{
    connections_.clear();
}

void World::insertEntity(std::unique_ptr<Entity>&& entity)
{
    if (not entity) {
        throw std::runtime_error("Warning: You can't add a null entity.");
    }

    // Stops an entity being added several times
    if (boost::find(entities_, entity) != std::end(entities_)) {
        throw std::invalid_argument("Entity already added");
    }

    entity->setWorld(this);
    entity->setParent(this->camera);
    entity->onAdded();
    entities_.push_back(std::move(entity));
}

void World::moveEntity(observing_ptr<World> world, observing_ptr<Entity> entity)
{
    if (not entity) {
        Game::log << "Warning: attempted to move null entity." << std::endl;
        return;
    }

    if (not world) {
        Game::log << "Warning: attempted to move entity to null world."
                  << std::endl;
        return;
    }

    // REVIEW: Shouldn't you warn somehow that you haven't actually moved
    //         this entity? AFAICT this is just aborting if the entity was
    //         going to be deleted this frame but won't attempt the move again?
    //
    // Response: if there are various events that could trigger an entity
    //           moving, and this coincides with an entity being removed, it's
    //           unlikely you want the entity to persist. It
    //           would be unpleasant to warn about this in an obstreperous
    //           manner. Could log to log.txt though.
    //           How could it attempt to move it again if it's been deleted?
    if (entity->isRemoved()) {
        // Don't let an entity escape deletion
        return;
    }

    toMove_.emplace_back(world, entity);

    // REVIEW: Ok so here's where updating_ is being checked!
    //         But, is this actually necessary? moveEntities() is going to get
    //         called at the end of a frame anyway...
    //
    // Response: Maybe not. Should look at this a bit more later.
    if (!updating_) {
        moveEntities();
    }
}

std::unique_ptr<Entity> World::releaseEntity(observing_ptr<Entity> entity)
{
    auto iter = boost::find(entities_, entity);

    // REVIEW: Shouldn't this throw an exception?
    //         (Possibly std::invalid_argument)
    if (iter == end(entities_)) {
        return nullptr;
    }

    auto ent = std::move(*iter);
    entities_.erase(iter);
    ent->removeParent();
    ent->onRemoved();
    return ent;
}

void World::update()
{
    // REVIEW: What is this? It's not thread safe or exception safe.
    updating_ = true;

    for (auto& entity : entities_) {
        entity->update();
    }

    addEntities();
    moveEntities();
    deleteEntities();
    updating_ = false;
}

void World::draw()
{
    boost::stable_sort(entities_, [](std::unique_ptr<Entity> const& e1,
                                     std::unique_ptr<Entity> const& e2) {
        return e1->getLayer() < e2->getLayer();
    });

    for (auto& entity : entities_) {
        entity->draw(camera);
    }
}

void World::addEntities()
{
    std::move(newEntities_.begin(), newEntities_.end(),
              std::back_inserter(entities_));
    newEntities_.clear();
}

void World::moveEntities()
{
    while (!toMove_.empty()) {
        observing_ptr<World> world = std::get<0>(toMove_.back());
        observing_ptr<Entity> entity = std::get<1>(toMove_.back());
        toMove_.pop_back();

        std::unique_ptr<Entity> entPtr = releaseEntity(entity);
        if (!entPtr.get()) {
            Game::log << "Entity not found in move operation" << std::endl;
            continue;
        }

        world->insertEntity(std::move(entPtr));
    }
}

void World::deleteEntities()
{
    boost::remove_erase_if(entities_, [](const std::unique_ptr<Entity>& ent) {
        if (ent->isRemoved()) {
            ent->onRemoved();
            return true;
        }
        return false;
    });
}

tank::observing_ptr<tank::EventHandler::Connection>
        World::connect(EventHandler::Condition condition,
                       EventHandler::Effect effect)
{
    auto cond = eventHandler.connect(condition, effect);
    connections_.push_back(std::move(cond));
    return connections_.back();
}
}
