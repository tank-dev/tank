#include "TextObject.hpp"

#include "../System/Game.hpp"

TextObject::TextObject(Vector const& pos,
                       char const* cText,
                       Uint32 duration)
:Entity    (pos),
 _duration (duration),
 _text     (NULL)
{
    //std::string sText(cText);
    //_displayTimer.start();
    //_text = new Text(pos,sText);
}

TextObject::~TextObject()
{
    //delete _text;
}

void TextObject::setText(char* cText)
{
	/*std::string sText(cText);
	if (_text != NULL)
	{
		delete _text;
	}
	_text = new Text(_pos,sText);*/
}

void TextObject::update()
{
    /*if(_duration != 0 && _displayTimer.getTicks() >= _duration)
    {
        _state->removeEntity( this );
    }*/
}

void TextObject::draw(IRender *const render)
{
    //_text->draw(render);
}