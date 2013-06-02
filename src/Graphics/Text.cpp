#include "Text.hpp"

#include "../System/GameState.hpp"

Text::Text(Vector const& pos, char const*const text, unsigned int duration)
:Entity   (pos),
 _text    (text),
 _duration(duration)
{
    //std::string sText(cText);
    _displayTimer.start();
}

Text::~Text()
{
}

void Text::update()
{
    if(_duration != 0 && _displayTimer.getTicks() >= _duration)
    {
        _state->removeEntity(this);
    }
}

void Text::draw(IRender *const render)
{
    //Render::Instance()->DrawSurface(_text,_pos);
    //TODO Make this work properly
    render->drawText( _text.c_str(), _pos );
}

void Text::isInside(Entity *ent) {}
