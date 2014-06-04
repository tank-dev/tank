/* This file is part of Tank.
 *
 * Tank is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Lesser General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * Tank is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License and
 * the GNU Lesser General Public Licence along with Tank. If not, see
 * <http://www.gnu.org/licenses/>.
 *
 * Copyright 2013 (©) Jamie Bayne, David Truby, David Watson.
 */

#ifndef TANK_XBOXCONTROLLER_HPP
#define TANK_XBOXCONTROLLER_HPP

#include <array>
#include <vector>
#include <SFML/Window/Joystick.hpp>
#include "../Utility/Vector.hpp"
#include "../Utility/observing_ptr.hpp"

namespace tank
{

class Controller
{
    friend class Controllers;
    bool connectedState_, connectedLast_;
    unsigned id_;
    std::array<double, sf::Joystick::AxisCount> axisStates_{};
    std::array<double, sf::Joystick::AxisCount> axisLast_{};
    std::array<bool, sf::Joystick::ButtonCount> buttonStates_{};
    std::array<bool, sf::Joystick::ButtonCount> buttonLast_{};

public:
    enum class Button;
    enum class Axis;

    Controller(unsigned id);

    bool buttonPressed(unsigned button) const;
    bool buttonPressed(Button button) const;
    std::function<bool()> ButtonPress(unsigned button) const;
    std::function<bool()> ButtonPress(Button button) const;

    bool buttonReleased(unsigned button) const;
    bool buttonReleased(Button button) const;
    std::function<bool()> ButtonRelease(unsigned button) const;
    std::function<bool()> ButtonRelease(Button button) const;

    bool buttonDown(unsigned button) const;
    bool buttonDown(Button button) const;
    std::function<bool()> ButtonDown(unsigned button) const;
    std::function<bool()> ButtonDown(Button button) const;

    bool buttonUp(unsigned button) const;
    bool buttonUp(Button button) const;
    std::function<bool()> ButtonUp(unsigned button) const;
    std::function<bool()> ButtonUp(Button button) const;

    std::function<bool()> AxisMoved(unsigned axis,
                                    double threshold = 0.05) const;
    std::function<bool()> AxisMoved(Axis axis, double threshold = 0.05) const;

    bool isConnected() const
    {
        return connectedState_;
    }
    std::function<bool()> Connected() const;
    std::function<bool()> Disconnected() const;

    double axisPosition(unsigned axis) const;
    double axisPosition(Axis axis) const;
    double axisDelta(unsigned axis) const;
    double axisDelta(Axis axis) const;

    Vectord leftStick() const;
    Vectord leftStickDelta() const;
    Vectord rightStick() const;
    Vectord rightStickDelta() const;
    Vectord directionPad() const;
    Vectord directionPadDelta() const;
    double leftTrigger() const;
    double leftTriggerDelta() const;
    double rightTrigger() const;
    double rightTriggerDelta() const;

private:
    void reset();
    void setStatus(bool connected)
    {
        connectedState_ = connected;
    }
};

enum class Controller::Button {
    A = 0,
    B = 1,
    X = 2,
    Y = 3,
    BUMPER_LEFT = 4,
    BUMPER_RIGHT = 5,
    BACK = 6,
    START = 7,
    XBOX = 8,
    STICK_LEFT = 9,
    STICK_RIGHT = 10
};

enum class Controller::Axis {
    STICK_LEFT_X = 0,
    STICK_LEFT_Y = 1,
    TRIGGER_LEFT = 2,
    TRIGGER_RIGHT = 3,
    STICK_RIGHT_X = 4,
    STICK_RIGHT_Y = 5,
    DPAD_X = 6,
    DPAD_Y = 7
};

class Controllers
{
    friend class Game;
    static std::vector<Controller> controllers_;

public:
    static std::vector<tank::observing_ptr<Controller>>
            getConnectedControllers();

    static std::vector<Controller> const& getAllControllers();

private:
    static void reset();
    static void initialize();
    static void setStatus(unsigned controllerID, bool connected);
    static void setButton(unsigned controllerID, unsigned button, bool state);
    static void setAxis(unsigned controllerID, unsigned axis, double position);
};

} /* namespace tank */

#endif /* TANK_XBOXCONTROLLER_HPP */
