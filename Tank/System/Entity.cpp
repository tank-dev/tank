// Copyright (©) Jamie Bayne, David Truby, David Watson 2013-2014.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt)

#include "Entity.hpp"

#include <cmath>
#include <stdexcept>
#include <algorithm>
#include <boost/range/algorithm.hpp>
#include <boost/range/algorithm_ext.hpp>
#include "Game.hpp"
#include "World.hpp"

namespace tank
{

int Entity::numEnts_ = 0;

Entity::Entity(Vectorf pos) 
    : Transformable(pos)
    , actorID_(numEnts_++)
{
}

void Entity::draw(Camera const& cam)
{
    for (auto& g : graphics_) {
        if (g->isVisible()) {
            g->draw();
        }
    }
}

std::vector<observing_ptr<Entity>>
        Entity::collide(std::vector<std::string> colTypes)
{
    std::vector<std::unique_ptr<Entity>> const& orig = world_->getEntities();
    std::vector<observing_ptr<Entity>> ents;
    std::vector<observing_ptr<Entity>> collisions;

    for (auto& unique : orig) {
        if (not unique->getTypes().empty()) {
            ents.emplace_back(unique);
        }
    }

    if (not colTypes.empty()) {
        ents.erase(
                std::remove_if(ents.begin(), ents.end(),
                               [&colTypes](observing_ptr<Entity> const& ent) {
                    auto& entTypes = ent->getTypes();
                    return std::find_first_of(entTypes.begin(), entTypes.end(),
                                              colTypes.begin(),
                                              colTypes.end()) == entTypes.end();
                }),
                ents.end());
    }

    for (auto& ent : ents) {
        if (ent != this) {
            Rectd const& A = hitbox_;
            Rectd const& B = ent->getHitbox();

            const double leftA = A.x + getPos().x;
            const double leftB = B.x + ent->getPos().x;
            const double rightA = leftA + A.w;
            const double rightB = leftB + B.w;
            const double topA = A.y + getPos().y;
            const double topB = B.y + ent->getPos().y;
            const double bottomA = topA + A.h;
            const double bottomB = topB + B.h;

            if (leftA > rightB or topA > bottomB or rightA < leftB or bottomA <
                topB) {
                continue;
            }

            collisions.push_back(ent);
        }
    }

    return collisions;
}

std::unique_ptr<Graphic> const& Entity::getGraphic(unsigned int i) const
{
    if (i < graphics_.size()) {
        return graphics_[i];
    }
    throw std::invalid_argument("getGraphic called with invalid index");
}

void Entity::insertGraphic(std::unique_ptr<Graphic>&& graphic)
{
    if (not graphic) {
        Game::log << "Warning: You can't add a null graphic." << std::endl;
        return;
    }

    // Stops an entity being added several times
    auto entityIter = boost::range::find_if(
            graphics_, [&graphic](std::unique_ptr<Graphic>& existing) {
                return graphic.get() == existing.get();
            });

    if (entityIter != end(graphics_)) {
        throw std::invalid_argument("Entity already added");
    }

    // If no hitbox, set to image bounds
    if (getHitbox() == Rectd() and getGraphicList().empty()) {
        auto hb = graphic->getSize();
        setHitbox(Rectd(0, 0, hb.x, hb.y));
    }

    graphics_.push_back(std::move(graphic));
}

void Entity::clearGraphics()
{
    graphics_.clear();
}

// Note: In hindsight, this isn't such a good idea. The only useful condition
// will be collision, and this method doesn't handle collision very well.
bool Entity::moveBy(Vectorf disp, std::function<bool()> cond)
{
    while (abs(disp.x) >= 1. || abs(disp.y) >= 1.) {
        auto oldPos = getPos();

        if (disp.x >= 1.) {
            setPos(getPos() + Vectorf{1, 0});
            --disp.x;
        } else if (disp.x <= -1.) {
            setPos(getPos() + Vectorf{-1, 0});
            ++disp.x;
        }

        // Check x
        if (cond()) {
            setPos(oldPos);
        }

        if (disp.y >= 1.) {
            setPos(getPos() + Vectorf{0, 1});
            --disp.y;
        } else if (disp.y <= -1.) {
            setPos(getPos() + Vectorf{0, -1});
            ++disp.y;
        }

        // Check y
        if (cond()) {
            setPos(oldPos);
        }

        // Have we moved at all?
        if (getPos() == oldPos) {
            return false;
        }
    }

    return true;
}

void Entity::moveBy(Vectorf disp)
{
    setPos(getPos() + disp);
}

void Entity::setHitbox(Rectd hitbox)
{
    hitbox_ = hitbox;
}

void Entity::setType(std::string type)
{
    types_.clear();
    types_.push_back(type);
}

void Entity::addType(std::string type)
{
    if (type == "")
        return;
    if (std::find(types_.begin(), types_.end(), type) == types_.end()) {
        types_.push_back(type);
    }
}

void Entity::setLayer(int layer)
{
    layer_ = layer;
}

void Entity::setWorld(const observing_ptr<World> world)
{
    world_ = world;
}

observing_ptr<EventHandler::Connection>
        Entity::connect(EventHandler::Condition condition,
                        EventHandler::Effect effect)
{
    auto cond = getWorld()->eventHandler.connect(condition, effect);
    connections_.push_back(std::move(cond));
    return connections_.back();
}

bool Entity::offScreen() const
{
    auto pos = getPos();
    auto size = getGraphic()->getSize();

    if (pos.y + size.y < 0 || pos.y > Game::window()->getSize().y ||
        pos.x + size.x < 0 || pos.x > Game::window()->getSize().x) {
        return true;
    }

    return false;
}

bool Entity::onScreen() const
{
    auto pos = getPos();
    auto size = getGraphic()->getSize();

    if (pos.y < 0 || pos.y + size.y > Game::window()->getSize().y ||
        pos.x < 0 || pos.x + size.x > Game::window()->getSize().x) {
        return false;
    }
    return true;
}

bool Entity::partOffScreen() const
{
    return (!onScreen()) && (!offScreen());
}
}
