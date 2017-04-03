/*
 * Copyright 2015-2017 Canonical Ltd.
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of version 3 of the GNU Lesser General Public
 * License as published by the Free Software Foundation.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with this library; if not, write to the
 * Free Software Foundation, Inc., 51 Franklin Street, Fifth Floor,
 * Boston, MA 02110-1301, USA.
 */

#pragma once

#include <sstream>

namespace unity
{

namespace util
{

    class Logger: public std::ostringstream
    {
    public:
        enum class Level {
            DEBUG = 0,
            INFO,
            MESSAGE,
            WARNING,
            CRITICAL,
            ERROR,
        };

        Logger(Logger::Level level, const std::string& domain);
        Logger(Logger&& logger);

        virtual ~Logger();

    private:
        Level _level;
        std::string _domain;
    };

// These are the APIs to be used for logging.
#define debug() Logger(Logger::Level::DEBUG, G_LOG_DOMAIN)
#define info() Logger(Logger::Level::INFO, G_LOG_DOMAIN)
#define warn() Logger(Logger::Level::WARNING, G_LOG_DOMAIN)
#define critical() Logger(Logger::Level::CRITICAL, G_LOG_DOMAIN)
#define error() Logger(Logger::Level::ERROR, G_LOG_DOMAIN)

} // namespace util

} // namespace unity
