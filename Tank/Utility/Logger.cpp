// Copyright (©) Jamie Bayne, David Truby, David Watson 2013-2014.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt)

#include "Logger.hpp"

namespace tank
{

void Logger::log(const std::string& s)
{
    logFile_ << "[" << timer_.getHumanTime() << "] " << s;
#ifdef DEBUG
    std::clog << "[" << fileName_ << ": " << timer_.getHumanTime() << "] " << s;
#endif
}

Logger::Logger(std::string file)
    : std::ostream(&buf_)
    , fileName_{file}
    , logFile_{fileName_}
    , buf_{[this](const std::string& s) { log(s); }}
{
    timer_.start();
    *this << "Log file created" << std::endl;
}

Logger::~Logger() throw()
{
    *this << "Closing log file" << std::endl;
}
}
