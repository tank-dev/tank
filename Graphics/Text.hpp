#ifndef TANK_TEXT_HPP
#define	TANK_TEXT_HPP

#include "../System/Entity.hpp"
#include "../Utility/Timer.hpp"
#include "../Utility/Vector.hpp"

#include <string>

namespace tank {

class Text
{
public:
    Text(std::string text);
    ~Text();
private:
    std::string  text_;
};

}
#endif
