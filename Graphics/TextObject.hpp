/*
 * File:   TextObject.hpp
 * Author: jamie
 *
 * Created on 18 December 2011, 01:43
 */

#ifndef TEXTOBJECT_H
#define	TEXTOBJECT_H

#include <string>
#include "../System/Entity.hpp"

#include "../Utility/Timer.hpp"
#include "Text.hpp"

enum TextBox
{
    NONE,
    MAIN,
    OTHER
};

class GameState;

class TextObject : public Entity
{
public:
    void update();
    void draw(IRender* const);

    void setText(std::string);

    void isInside(Entity*) {}

    TextObject(Vectorf const& pos, std::string, Uint32 duration = 0);
    ~TextObject();
private:
    Uint32  _duration;
    Timer   _displayTimer;
    TextBox _textBox;
    Text*   _text;
};


#endif /* TEXTOBJECT_H */
