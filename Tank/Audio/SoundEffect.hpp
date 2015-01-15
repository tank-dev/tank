// Copyright (©) Jamie Bayne, David Truby, David Watson 2013-2014.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt)

#ifndef TANK_SOUNDEFFECT_HPP
#define TANK_SOUNDEFFECT_HPP

#include <memory>
#include <string>
#include <SFML/Audio/Sound.hpp>
#include <SFML/Audio/SoundBuffer.hpp>
#include <Tank/Utility/Vector.hpp>

namespace tank
{

/*!
 * \brief Store and play a sound effect.
 *
 * This is intended for playing in-game sound effects. It stores the sound file
 * in memory after loading, allowing the effect to be played quickly when needed
 * at the cost of memory. As such, if you have a large sound file, for example
 * background music, you should use tank::Music.
 *
 * The sound system supports the following file formats: ogg, wav, flac, aiff,
 * au, raw, paf, svx, nist, voc, ircam, w64, mat4, mat5 pvf, htk, sds, avr, sd2,
 * caf, wve, mpc2k, rf64.
 */
class SoundEffect
{
    std::shared_ptr<sf::SoundBuffer> buffer_ = std::make_shared<sf::SoundBuffer>();
    sf::Sound sound_;
    bool loaded_ {false};

public:
    using Status = sf::Sound::Status;
    SoundEffect() = default;
    SoundEffect(std::string fileName);
    SoundEffect(SoundEffect const&) = default;
    SoundEffect& operator=(SoundEffect const&) = default;

    bool load(std::string fileName);
    bool loadFromFile(std::string fileName) { return load(fileName); }

    void play() { sound_.play(); }
    void pause() { sound_.pause(); }
    void stop() { sound_.stop(); }
    void setLoop(bool loop) { return sound_.setLoop(loop); }
    bool getLoop() const { return sound_.getLoop(); }
    void setPosition(Vectorf pos) { sound_.setPosition({pos.x, pos.y,0}); }
    Vectorf getPosition() const;
    void setRelativeToListener(bool rel) { sound_.setRelativeToListener(rel); }
    bool isRelativeToListener() const { return sound_.isRelativeToListener(); }
    void setVolume(float v) { sound_.setVolume(v); }
    float getVolume() const { return sound_.getVolume(); }
    void setAttenuation(float attenuation) { sound_.setAttenuation(attenuation); }
    float getAttenuation() const { return sound_.getAttenuation(); }
    void setMinDistance(float distance) { sound_.setMinDistance(distance); }
    float getMinDistance() const { return sound_.getMinDistance(); }

    explicit operator bool()
    {
        return loaded_;
    }

    Status getStatus()
    {
        return sound_.getStatus();
    }
};
}

#endif // TANK_SOUNDEFFECT_HPP
