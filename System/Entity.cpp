#include "Entity.hpp"

#include <cmath>
#include <algorithm>
#include "State.hpp"

int Entity::numEnts_ = 0;

Entity::Entity(Vectorf const& pos)
    : actorID_(numEnts_++),
      layer_(0),
      pos_(pos),
      hitbox_({0}),
      texture_(nullptr),
      //state_ (state),
      type_(""),
      solid_(false),
      visible_(true)
{
}

Entity::~Entity() {}

//Default draw function
void Entity::draw(IRender* const render)
{
    if(texture_)
    {
        render->draw(texture_, pos_);
    }
}

void Entity::setState(State* const state)
{
    state_ = state;
}

void Entity::setPos(Vectorf const& pos)
{
    pos_ = pos;
}

std::vector<Entity*> Entity::collide(std::string type)
{ 
    auto entList = state_->getEntities();
    std::vector<Entity*> collisions;

    if(type != "")
    {
        entList.erase(std::remove_if(entList.begin(), entList.end(),
                                     [type](Entity* ent)
        {
            return ent->getType() != type;
        }), entList.end());
    }

    for(auto ent : entList)
    {
        if(ent != this)
        {
            Rect const& A = hitbox_;
            Rect const& B = ent->getHitBox();

            double leftA   = A.x + pos_.x;
            double leftB   = B.x + ent->getPos().x;
            double rightA  = A.x + A.w + pos_.x;
            double rightB  = B.x + B.w + ent->getPos().x;
            double topA    = A.y + pos_.y;
            double topB    = B.y + ent->getPos().y;
            double bottomA = A.y + A.h + pos_.y;
            double bottomB = B.y + B.h + ent->getPos().y;

            if(leftA > rightB) continue;
            if(topA > bottomB) continue;
            if(rightA < leftB) continue;
            if(bottomA < topB) continue;

            collisions.push_back(ent);
        } 
    }

    return collisions;
}
