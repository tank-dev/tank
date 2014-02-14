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

#include "Controller.hpp"

#include <algorithm>
#include <iterator>
#include <cmath>

namespace tank {

std::vector<Controller> Controllers::controllers_;

void Controllers::initialize()
{
    for (int i = 0; i < sf::Joystick::Count; ++i)
    {
        controllers_.emplace_back(i);
    }
}

void Controllers::reset()
{
    for (auto&& c : controllers_)
    {
        c.reset();
    }
}

void Controllers::setStatus(unsigned id, bool connected)
{
    controllers_[id].setStatus(connected);
}

void Controllers::setButton(unsigned id, unsigned button, bool state)
{
    controllers_[id].buttonStates_[button] = state;
}

void Controllers::setAxis(unsigned id, unsigned axis, double position)
{
    controllers_[id].axisStates_[axis] = position;
}

std::vector<tank::observing_ptr<Controller>>
Controllers::getConnectedControllers()
{
    std::vector<tank::observing_ptr<Controller>> cs;
    std::copy_if(controllers_.begin(), controllers_.end(),
                 std::back_inserter(cs), std::mem_fn(&Controller::isConnected));
    return cs;
}

std::vector<Controller> const& Controllers::getAllControllers()
{
    return controllers_;
}

Controller::Controller(unsigned id)
    : id_{id}
{
    connectedState_ = connectedLast_ = sf::Joystick::isConnected(id);
}

void Controller::reset()
{
    if (connectedState_)
    {
        std::copy(axisStates_.begin(),axisStates_.end(), axisLast_.begin());
        std::copy(buttonStates_.begin(),buttonStates_.end(), buttonLast_.begin());
    }
    else if (connectedLast_)
    {
        std::fill(axisStates_.begin(),axisStates_.end(), 0.0);
        std::fill(buttonStates_.begin(),buttonStates_.end(), false);
    }
    connectedLast_ = connectedState_;
}

bool Controller::buttonPressed(unsigned button) const
{
    return buttonStates_[button] and not buttonLast_[button];
}
bool Controller::buttonPressed(Button button) const
{
    return buttonPressed(static_cast<unsigned>(button));
}
std::function<bool()> Controller::ButtonPress(unsigned button) const
{
    return [&] {
        return buttonPressed(button);
    };
}
std::function<bool()> Controller::ButtonPress(Button button) const
{
    return [&] {
        return buttonPressed(button);
    };
}

bool Controller::buttonReleased(unsigned button) const
{
    return buttonLast_[button] and not buttonStates_[button];
}
bool Controller::buttonReleased(Button button) const
{
    return buttonReleased(static_cast<unsigned>(button));
}
std::function<bool()> Controller::ButtonRelease(unsigned button) const
{
    return [&] {
        return buttonReleased(button);
    };
}
std::function<bool()> Controller::ButtonRelease(Button button) const
{
    return [&] {
        return buttonReleased(button);
    };
}

bool Controller::buttonDown(unsigned button) const
{
    return buttonStates_[button];
}
bool Controller::buttonDown(Button button) const
{
    return buttonDown(static_cast<unsigned>(button));
}
std::function<bool()> Controller::ButtonDown(unsigned button) const
{
    return [&] {
        return buttonDown(button);
    };
}
std::function<bool()> Controller::ButtonDown(Button button) const
{
    return [&] {
        return buttonDown(button);
    };
}

bool Controller::buttonUp(unsigned button) const
{
    return not buttonDown(button);
}
bool Controller::buttonUp(Button button) const
{
    return not buttonDown(button);
}
std::function<bool()> Controller::ButtonUp(unsigned button) const
{
    return [&] {
        return buttonUp(button);
    };
}
std::function<bool()> Controller::ButtonUp(Button button) const
{
    return [&] {
        return buttonUp(button);
    };
}

std::function<bool()> Controller::AxisMoved(unsigned axis, double threshold) const
{
    return [&] {
        return std::fabs(axisDelta(axis)) > threshold;
    };
}
std::function<bool()> Controller::AxisMoved(Axis axis, double threshold) const
{
    return [&] {
        return std::fabs(axisDelta(axis)) > threshold;
    };
}

std::function<bool()> Controller::Connected() const
{
    return [&] {
        return connectedState_ and not connectedLast_;
    };
}
std::function<bool()> Controller::Disconnected() const
{
    return [&] {
        return connectedLast_ and not connectedState_;
    };
}

double Controller::axisPosition(unsigned axis) const
{
    return axisStates_[axis] / 100.;
}
double Controller::axisPosition(Axis axis) const
{
    return axisPosition(static_cast<int>(axis));
}
double Controller::axisDelta(unsigned axis) const
{
    return axisPosition(axis) - axisLast_[axis] / 100.;
}
double Controller::axisDelta(Axis axis) const
{
    return axisDelta(static_cast<int>(axis));
}

/* 360 specific */
Vectord Controller::leftStick() const
{
    return {axisPosition(Axis::STICK_LEFT_X),axisPosition(Axis::STICK_LEFT_Y)};
}
Vectord Controller::leftStickDelta() const
{
    return {axisDelta(Axis::STICK_LEFT_X),axisDelta(Axis::STICK_LEFT_Y)};
}
Vectord Controller::rightStick() const
{
    return {axisPosition(Axis::STICK_RIGHT_X),axisPosition(Axis::STICK_RIGHT_Y)};
}
Vectord Controller::rightStickDelta() const
{
    return {axisDelta(Axis::STICK_RIGHT_X),axisDelta(Axis::STICK_RIGHT_Y)};
}
Vectord Controller::directionPad() const
{
    return {axisPosition(Axis::DPAD_X),axisPosition(Axis::DPAD_Y)};
}
Vectord Controller::directionPadDelta() const
{
    return {axisDelta(Axis::DPAD_X),axisDelta(Axis::DPAD_Y)};
}
double Controller::leftTrigger() const
{
    return axisPosition(Axis::TRIGGER_LEFT);
}
double Controller::leftTriggerDelta() const
{
    return axisDelta(Axis::TRIGGER_LEFT);
}
double Controller::rightTrigger() const
{
    return axisPosition(Axis::TRIGGER_RIGHT);
}
double Controller::rightTriggerDelta() const
{
    return axisDelta(Axis::TRIGGER_RIGHT);
}
}
