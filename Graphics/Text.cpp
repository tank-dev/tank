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
        remove();
    }
}

void Text::draw(IRender* const render)
{
    //TODO Make this work properly
    render->drawText(text_.c_str(), getPos());
}
