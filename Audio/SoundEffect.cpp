#include "SoundEffect.hpp"
#include "../System/Game.hpp"

namespace tank {

SoundEffect::SoundEffect(std::string fileName)
{
    load(fileName);
}

bool SoundEffect::load(std::string fileName)
{
    if (loaded_) {
        Game::log << "SoundEffect already loaded!" << std::endl;
        return loaded_;
    }
    loaded_ = buffer_.loadFromFile(fileName);
    sound_.setBuffer(buffer_);
    return loaded_;
}

void SoundEffect::play()
{
    sound_.play();
}

}
