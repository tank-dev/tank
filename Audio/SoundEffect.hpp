#ifndef TANK_SOUNDEFFECT_HPP
#define TANK_SOUNDEFFECT_HPP

#include <string>
#include <SFML/Audio/Sound.hpp>
#include <SFML/Audio/SoundBuffer.hpp>

namespace tank {

class SoundEffect
{
    sf::SoundBuffer buffer_;
    sf::Sound sound_;
    bool loaded_ = false;

public:
    SoundEffect(std::string fileName);

    bool load(std::string fileName);

    void play();

    explicit operator bool()
    {
        return loaded_;
    }

};

}

#endif //TANK_SOUNDEFFECT_HPP
