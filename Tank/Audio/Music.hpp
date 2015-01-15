// Copyright (©) Jamie Bayne, David Truby, David Watson 2013-2014.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt)
#ifndef TANK_MUSIC_HPP
#define TANK_MUSIC_HPP

#include <string>
#include <memory>
#include <SFML/Audio/Music.hpp>

namespace tank
{

class Music
{
    std::shared_ptr<sf::Music> music_ = std::make_shared<sf::Music>();
    bool loaded_ = false;

public:
    /*!
     * \brief Construct an empty Music.
     *
     * Playing an empty music will do nothing and print a warning, so before
     * attempting to play either Music::load() the file or use the other
     * constructor.
     */
    Music() = default;

    /*!
     * \brief Construct a Music from the file at the given path.
     *
     * This loads the music file at the given filename. It has the same effect
     * as constructing an empty Music and then calling Music::load() on it.
     *
     * Supports the following formats: ogg, wav, flac, aiff, au, raw, paf, svx,
     * nist, voc, ircam, w64, mat4, mat5 pvf, htk, sds, avr, sd2, caf, wve,
     * mpc2k, rf64.
     */
    Music(std::string fileName);

    /*!
     * \brief Default copy constructor.
     *
     * This shallow copies the music file, so is effectively cost-free.
     */
    Music(Music const&) = default;

    /*!
     * \brief Default copy assignment operator.
     *
     * This shallow copies the music file, so is effectively cost-free.
     */
    Music& operator=(Music const&) = default;

    /*!
     * \brief Load a music file from the given path.
     *
     * Supports the following formats: ogg, wav, flac, aiff, au, raw, paf, svx,
     * nist, voc, ircam, w64, mat4, mat5 pvf, htk, sds, avr, sd2, caf, wve,
     * mpc2k, rf64.
     *
     * \param fileName The path to load the music file from.
     * \return false if the file failed to load, true otherwise
     */
    bool load(std::string fileName);

    // TODO: Why does this exist?
    /*!
     * \brief See: Music::load()
     */
    bool loadFromFile(std::string fileName) {return load(fileName);}

    /*!
     * \brief Play the contained music.
     *
     * If the music is empty, logs that fact and does nothing.
     */
    void play();

    /*!
     * \brief Pause the contained music.
     *
     * If the music is empty, logs that fact and does nothing.
     */
    void pause();

    /*!
     * \brief Stop the contained music.
     *
     * If the music is empty, logs that fact and does nothing.
     */
    void stop();

    /*!
     * \brief Set the volume of the music.
     *
     * If the music is empty, logs that fact and does nothing.
     *
     * \param v The volume of the music as a value between 0 and 100.
     */
    void setVolume(float v);

    /*!
     * \brief Get the volume of the music.
     *
     * If the music is empty, logs that fact and does nothing.
     *
     * \return The current volume of the music as a value between 0 and 100.
     */
    float getVolume();

    /*!
     * \brief Set whether the music will loop or not.
     *
     * If the music is empty, logs that fact and does nothing.
     *
     * \param loop `true` if music looping is desired, `false` otherwise.
     */
    void setLoop(bool loop);

    /*!
     * \brief Get whether the music will loop or not.
     *
     * If the music is empty, logs that fact and does nothing.
     *
     * \return `true` if music will loop, `false` otherwise.
     */
    bool getLoop();

    /*!
     * \brief Check if the music is loaded.
     *
     * \return `true` if music is loaded, `false` otherwise.
     */
    explicit operator bool()
    {
        return loaded_;
    }
};
}

#endif // TANK_MUSIC_HPP
