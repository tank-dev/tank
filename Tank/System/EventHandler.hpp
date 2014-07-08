// Copyright (©) Jamie Bayne, David Truby, David Watson 2013-2014.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt)

#ifndef TANK_EVENTS_HPP
#define TANK_EVENTS_HPP

#include <memory>
#include <set>
#include <functional>
#include <SFML/Window/Event.hpp>

namespace tank
{

/*!
 * \brief A class for registering event callbacks
 *
 * An event consists of a condition and an effect.
 * A condition is a function which returns a bool, and an effect is a void
 * function with side-effects.
 *
 * Events are registered using EventHandler.connect(), and triggered by
 * EventHandler.propagate().
 *
 * \see Keyboard
 * \see Mouse
 * \see Controller
 */
class EventHandler
{
public:
    class Connection;

    using Condition = std::function<bool()>;
    using Effect = std::function<void()>;

private:
    class ConnectedPair
    {
        static std::size_t counter;
        std::size_t uid;

    public:
        Condition condition;
        Effect effect;

        ConnectedPair(Condition condition, Effect effect)
                : uid{counter}, condition{condition}, effect{effect}
        {
            ++counter;
        }

        // std::set boilerplate
        bool operator<(const ConnectedPair& rhs) const
        {
            return this->uid < rhs.uid;
        }
    };

    using ConnectedPairList = std::set<ConnectedPair>;
    ConnectedPairList connections;

    void disconnect(Connection& connection);

public:
    // FIXME: "connect" isn't really a good name for this function. Something
    // along the lines of "register" might be better.
    /*!
     * \brief Register a Condition/Effect pair.
     *
     * A condition is a function which returns a bool, and an effect is a void
     * function with side-effects. Either can be any of the types implicitly
     * convertable to std::function: std::functions, function pointers, lambdas.
     *
     * The format is
     * `connect(condition [&& condition...] [|| condition...], effect)`
     * where condition functions can be &&'d and ||'d together to make a new
     * condition.
     *
     * connect() returns an EventHandler::Connection, which will disconnect the
     * event when it is destroyed. Thefore, you must store connections that you
     * want to persist.
     *
     * Example:
     *
     * ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~{.cpp}
     * class MyEnt : public tank::Entity
     * {
     *     std::unique_ptr<tank::EventHandler::Connection> a,b,c;
     *
     * public:
     *     // Must manage connections in onAdded, as getWorld() is not set at
     *     // construction
     *     virtual void onAdded() override
     *     {
     *         using Kbd = tank::Keyboard;
     *         using Key = tank::Key;
     *         auto& eh = getWorld().eventHandler;
     *         a = eh.connect(Kbd::KeyDown(Key::Left), moveLeft);
     *         b = eh.connect(Kbd::KeyDown(Key::Right), moveRight);
     *         c = eh.connect(Kbd::KeyDown(Key::Space) || 
     *                        Kbd::KeyDown(Key::Enter),
     *                        jump);
     *     }
     * };
     * ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
     *
     * where `moveLeft`, `moveRight` and `jump` are functions describing the
     * desired behaviour.
     *
     * Entity::connect() and World::connect() automate the storage process for
     * Entity and World lifespans, so the above example can be shortened:
     *
     * ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~{.cpp}
     * class MyEnt : public tank::Entity
     * {
     * public:
     *     // Must manage connections in onAdded, as getWorld() is not set at
     *     // construction
     *     virtual void onAdded() override
     *     {
     *         using Kbd = tank::Keyboard;
     *         using Key = tank::Key;
     *         connect(Kbd::KeyDown(Key::Left), moveLeft);
     *         connect(Kbd::KeyDown(Key::Right), moveRight);
     *         connect(Kbd::KeyDown(Key::Space) ||
     *                 Kbd::KeyDown(Key::Enter),
     *                 jump);
     *     }
     * };
     * ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
     *
     * \param condition A function object which takes no arguments and returns a
     * bool indicating true when effect should be called
     * \param effect A void function object which will be called when condition
     * returns true
     */
    std::unique_ptr<Connection> connect(Condition condition, Effect effect);

    /*!
     * \brief Check registered events, triggering each effect if its condition
     * returns true.
     *
     * On the event handler of the active World, this is called every frame
     * before World::update() and World::draw() -- therefore, you should not
     * need to call it yourself.
     */
    void propagate();

    EventHandler() = default;
    EventHandler(EventHandler const&) = delete;
    EventHandler& operator=(EventHandler const&) = delete;
};

class EventHandler::Connection
{
    EventHandler& events;
    ConnectedPairList::iterator iterator;
    bool connected = true;

public:
    Connection(EventHandler& events, ConnectedPairList::iterator iterator)
            : events(events), iterator(iterator)
    {
    }

    ~Connection()
    {
        disconnect();
    }

    void disconnect()
    {
        if (not connected) {
            return;
        } // REVIEW: This will never happen
        connected = false;
        events.disconnect(*this);
    }

    ConnectedPairList::iterator getIterator()
    {
        return iterator;
    }

    bool isConnected() const
    {
        return connected;
    }
};

inline std::function<bool()> fnot(std::function<bool()> f)
{
    return [f]() { return !f(); };
}
}

inline std::function<bool()> operator&&(std::function<bool()> f1,
                                        std::function<bool()> f2)
{
    return [f1, f2]() { return f1() && f2(); };
}

inline std::function<bool()> operator||(std::function<bool()> f1,
                                        std::function<bool()> f2)
{
    return [f1, f2]() { return f1() || f2(); };
}

#endif // TANK_EVENTS_HPP
