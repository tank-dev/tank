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

#include "Entity.hpp"

#include <cmath>
#include <stdexcept>
#include <algorithm>
#include "State.hpp"

namespace tank {

int Entity::numEnts_ = 0;

Entity::Entity(Vectorf pos)
    : pos_(pos)
    , rot_(0)
    , hitbox_({0,0,0,0})
    , type_("")
    , solid_(false)
    , layer_(0)
    , state_ (nullptr)
    , actorID_(numEnts_++)
{}

Entity::~Entity() {}

//Default draw function
void Entity::draw(Vectorf camera)
{
    for(auto& g : graphics_)
    {
        g->draw(getPos(), getRotation(), camera);
    }
}

std::vector<observing_ptr<Entity>> Entity::collide(std::string type)
{
    std::vector<std::unique_ptr<Entity>> const& origList =
            state_->getEntities();
    std::vector<observing_ptr<Entity>> entList;
    std::vector<observing_ptr<Entity>> collisions;

    for (auto& unique : origList)
    {
        if (type == "" or type == unique->getType())
        {
            entList.emplace_back(unique);
        }
    }

    for (auto ent : entList)
    {
        if (ent != this)
        {
            Rectd const& A = hitbox_;
            Rectd const& B = ent->getHitbox();

            const double leftA   = A.x + pos_.x;
            const double leftB   = B.x + ent->getPos().x;
            const double rightA  = A.x + A.w + pos_.x;
            const double rightB  = B.x + B.w + ent->getPos().x;
            const double topA    = A.y + pos_.y;
            const double topB    = B.y + ent->getPos().y;
            const double bottomA = A.y + A.h + pos_.y;
            const double bottomB = B.y + B.h + ent->getPos().y;

            if (leftA > rightB or topA > bottomB or
                rightA < leftB or bottomA < topB)
            {
                continue;
            }

            collisions.push_back(ent);
        }
    }

    return collisions;
}

std::unique_ptr<Graphic> const& Entity::getGraphic(unsigned int i) const
{
    if (graphics_.size() > i)
    {
        return graphics_[i];
    }
    throw std::invalid_argument("getGraphic called with invalid index");
}

void Entity::setPos(Vectorf pos)
{
    pos_ = pos;
}

void Entity::moveBy(Vectorf vec)
{
    //setPos({getPos().x + vec.x, getPos().y + vec.y});
    setPos(getPos() + vec);
}

void Entity::setRotation(float rot)
{
    rot_ = rot;
}

void Entity::setHitbox(Rectd hitbox)
{
    hitbox_ = hitbox;
}

void Entity::setSolid(bool solid)
{
    solid_ = solid;
}

void Entity::setLayer(int layer)
{
    layer_ = layer;
}

void Entity::setState(const observing_ptr<State> state)
{
    state_ = state;
}

tank::observing_ptr<tank::EventHandler::Connection> Entity::connect(
                                       EventHandler::Condition condition,
                                       EventHandler::Effect effect)
{
    auto cond = getState()->eventHandler.connect(condition, effect);
    connections.push_back(std::move(cond));
    return connections.back();
}

}
