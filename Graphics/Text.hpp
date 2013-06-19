#ifndef TEXT_H
#define	TEXT_H

#include "../System/Entity.hpp"
#include "../Utility/Timer.hpp"
#include "../Utility/Vector.hpp"

#include <string>

class Text
{
public:
    Text(std::string text);
    ~Text();
private:
    std::string  text_;
};
#endif
