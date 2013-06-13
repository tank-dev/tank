#include "Text.hpp"

#include "../System/State.hpp"

Text::Text(Vectorf const& pos, std::string text, unsigned int duration)
    :Entity(pos),
     text_(text),
     duration_(duration)
{
    //std::string sText(cText);
    displayTimer_.start();
}

Text::~Text()
{
}

void Text::update()
{
    if(duration_ != 0 && displayTimer_.getTicks() >= duration_)
    {
        state_->removeEntity(this);
    }
}

void Text::draw(IRender* const render)
{
    //Render::Instance()->DrawSurface(_text,_pos);
    //TODO Make this work properly
    render->drawText(text_.c_str(), pos_);
}

void Text::isInside(Entity* ent) {}
