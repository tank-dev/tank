#ifndef TANK_MUSIC_HPP
#define TANK_MUSIC_HPP

#include <string>
#include <SFML/Audio/Music.hpp>

namespace tank {

class Music {
    sf::Music music_;
    bool loaded_ = false;

public:
    Music(std::string fileName);

    bool load(std::string fileName);

    void play();
    void pause();
    void stop();

    explicit operator bool()
    {
        return loaded_;
    }
};

}

#endif //TANK_MUSIC_HPP
