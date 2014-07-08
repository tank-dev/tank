// Copyright (©) Jamie Bayne, David Truby, David Watson 2013-2014.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt)

#ifndef TANK_GAME_HPP
#define TANK_GAME_HPP

#include <stack>
#include <memory>
#include "../Utility/Timer.hpp"
#include "../Utility/Logger.hpp"
#include "../Utility/observing_ptr.hpp"
#include "Window.hpp"
#include "World.hpp"

namespace tank
{

/*!
 * \brief Static class controlling game loop, Window and World stack.
 *
 * # Game
 *
 * The Game class allows you to initialize, start and stop the game. It
 * provides control over the main game loop and the Worlds in the game.
 *
 * ## Starting a game
 *
 * To start the engine, call Game::initialize(). This will create the
 * window, and initialize rendering.
 *
 * Before starting the game, you should create a World with Game::makeWorld<>().
 * This will create a world and prepare to add it to the top of the world stack.
 * You can then call Game::run() to enter the main loop.
 *
 * Example Main.cpp:
 *
 * ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~{.cpp}
 *     int main()
 *     {
 *         if (tank::Game::initialize({windowX,windowY}, desiredFPS)) {
 *            tank::Game::makeWorld<MyMenuWorld>(); // Create a new world
 *            tank::Game::run(); // enter the game loop, which will add the
 *                               // created world to the top of the world stack
 *         }
 *     }
 * ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 *
 * One iteration of the main loop is equivalent to a frame.
 * At the beginning of a frame, the last of any worlds created in the last frame
 * with makeWorld() will be added to the top of the world stack. If the world
 * stack is empty, the loop will exit. Otherwise, the top of the stack will
 * become the active world. The active world will then be updated and drawn.
 * Finally, if popWorld() has been called, the active world will be destroyed,
 * and the next frame will begin.
 *
 * ##Managing Worlds
 *
 * Tank currently uses a simple stack to manage worlds. In a frame, you
 * can add one world to the top of the stack, and pop the currently active
 * world from the stack, destroying it.
 *
 * In the following example, rows below **Function** represent sequential
 * function calls in that frame, while rows above **Function** represent the
 * world stack at the beginning of each frame, going from the bottom up.
 * A World item in italics indicates that it is the current world.
 *
 * |      Start        |      Frame 1      |      Frame 2       |    Frame 3        | Frame 4
 * | :---------------: | :---------------: | :----------------: | :----------:      | :-:
 * |        -          |         -         |       *Main*       |       -           |  -
 * |        -          |      *Menu*       |        Menu        |    *Menu*         |  *Main*
 * |   **Function**    |   **Function**    |    **Function**    | **Function**      | **Function**
 * | makeWorld<Main>() | makeWorld<Main>() |     popWorld()     | makeWorld<Main>() |  popWorld()
 * | makeWorld<Menu>() |         -         |     popWorld()     |   popWorld()      |  -
 *
 * There are some important things to note:
 *
 *  - only the last makeWorld() call before the next frame will add that world
 *    to the stack; however, all makeWorld calls will *create* a world,
 *    calling its constructor, but all but the last will be destroyed.
 *  - multiple calls to popWorld() have no additional effect
 *  - calling popWorld() pops the *currently active* World, regardless of
 *    whether makeWorld() has been called.
 *  - if the World stack is empty at the beginning of a frame, the game loop
 *    ends.
 *
 * \see World
 * \see Logger
 */
class Game
{
    static bool initialized_;
    static bool run_;

    static bool popWorld_;

    static observing_ptr<World> currentWorld_;
    static std::unique_ptr<Window> window_;

    static std::stack<std::unique_ptr<World>> worlds_;
    static Timer frameTimer_;
    static std::unique_ptr<World> newWorld_;

public:

    Game() = delete;
    ~Game() = delete;
    /*!
     * \brief A log stream.
     *
     * This acts like a standard stream (_e.g._ `std::cout`), and writes to the
     * file `log.txt` in the directory in which the game was run.
     * If `DEBUG` is defined, it also outputs to `std::clog`.
     *
     * Tank writes to Game::log when initializing and closing, so `log.txt` can
     * show you if the engine is failing at some point.
     *
     * **NB:** remember to finish your log with `std::endl`.
     *
     * Example code:
     *
     * ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~{.cpp}
     *     MyEnt() : tank::Entity({0, 0})
     *     {
     *         Game::log << "Created MyEnt at position (0, 0)" << std::endl;
     *     }
     * ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
     *
     * Example `log.txt`:
     *
     *     [00:00:00.231] Log file created
     *     [00:00:00.400] Opening Window
     *     [00:00:00.641] Loading main state
     *     [00:00:00.700] Loading World...
     *     [00:00:00.710] Created MyEnt at position (0, 0)
     *     [00:00:00.714] Entering main loop
     *     [00:00:33.227] Unloading World...
     *     [00:00:33.230] Closing Window
     *     [00:00:33.233] Closing log file
     *
     */
    static Logger log;

    /*!
     * \brief Frame-rate of the game (60)
     *
     * \return Value passed to Game::initialize()
     */
    static unsigned int fps;

    // TODO work out why Controllers::initialize() doesn't auto-link
    /*!
     * \brief Initializes the Window and game
     *
     * Creates a window of usable size `windowSize` with an OpenGL rendering
     * context, and detects plugged in controllers.
     *
     * \param windowSize The window canvas size in pixels.
     * \return `true` on success.
     */
    static bool initialize(Vectoru windowSize, int fps = 60);

    /*! \brief Starts the game loop */
    static void run();

    /*!
     * \brief Removes the current World at the end of the frame.
     *
     * At the beginning of the next frame, one of two things will happen:
     *
     * - There is a world on top of the world stack: it will become active.
     * - The world stack is empty: the game loop will end.
     */
    static void popWorld();

    /*!
     * \brief Creates a World, which will become the active world next frame.
     *
     * This is a factory function which creates an instance of a class deriving
     * from World. The world is constructed immediately, passing the `args`
     * provided. At the beginning of the next frame, the world is pushed on top
     * of the world stack, making it the active world.
     *
     * **NB:** a second world created in a single frame will destroy the first.
     *
     * Example code:
     *
     * ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~{.cpp}
     *     class MyWorld : public tank::World
     *     {
     *     public:
     *         MyWorld(int a, char b) : tank::World() {}
     *     };
     *
     *     Game::makeWorld<MyWorld>(42, 'z');
     * ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
     *
     * \tparam T The type of world to create.
     * \param args Arguments to pass to T's constructor.
     *
     * \return A pointer of type T to the newly created World.
     */
    template <typename T, typename... Args>
    static observing_ptr<T> makeWorld(Args&&... args);

    /*! \brief Returns a pointer to the active World. */
    static observing_ptr<World> world()
    {
        return currentWorld_;
    }

    /*! \brief Returns a `const unique_ptr&` to the Window. */
    static std::unique_ptr<Window> const& window()
    {
        return window_;
    };

    /*!
     * \brief Stops the game loop
     *
     * This exits the game loop, but does not close the Window. This will effectively freeze your
     * window application, and may result in it being killed by the operating
     * system. The loop can be restarted (continuing the game where it left off)
     * by calling Game::run() again.
     *
     * You can avoid your application being killed by polling its events
     * manually with `Game::window.pollEvent()`.
     *
     * \see Window
     */
    //TODO: check the os will kill the app
    static void stop()
    {
        run_ = false;
    }

private:
    static void handleEvents();
    static void update();
    static void draw();
};

template <typename T, typename... Args>
observing_ptr<T> Game::makeWorld(Args&&... args)
{
    static_assert(std::is_base_of<World, T>::value,
                  "Class must derive from World");

    std::unique_ptr<T> world {new T(std::forward<Args>(args)...)};
    observing_ptr<T> ptr {world};
    // worlds_.push(std::move(world));
    newWorld_.reset(world.release());
    return ptr;
}
}

#endif
