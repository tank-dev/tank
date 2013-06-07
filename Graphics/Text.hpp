#ifndef TEXT_H
#define	TEXT_H

#include "../System/Entity.hpp"
#include "../Utility/Timer.hpp"
#include "../Utility/Vector.hpp"

#include <string>

class Text : public Entity
{
public:
    void update();
    void draw(IRender* const);

    void isInside(Entity*);

    Text(Vectorf const& pos, std::string text, unsigned int duration);
    ~Text();
private:
    std::string  _text;
    unsigned int _duration;
    Timer        _displayTimer;
};
#endif
