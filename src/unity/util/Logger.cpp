/*
 * Copyright 2017 Canonical Ltd.
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

#define G_LOG_DOMAIN nullptr

#include "unity/util/Logger.h"

#include <glib.h>

namespace unity
{

namespace util
{

Logger::Logger(Logger::Level level, const std::string& domain):
    std::ostringstream(""),
    _level(level),
    _domain(domain)
{
}

Logger::Logger(Logger&& logger):
    std::ostringstream(std::move(logger)),
    _level(logger._level)
{
}

Logger::~Logger()
{
    GLogLevelFlags glib_level;
    auto message = str();

    if (!message.empty()) {
        switch (_level) {
        case Logger::Level::DEBUG:
            glib_level = G_LOG_LEVEL_DEBUG;
            break;
        case Logger::Level::INFO:
            glib_level = G_LOG_LEVEL_INFO;
            break;
        case Logger::Level::MESSAGE:
            glib_level = G_LOG_LEVEL_MESSAGE;
            break;
        case Logger::Level::WARNING:
            glib_level = G_LOG_LEVEL_WARNING;
            break;
        case Logger::Level::CRITICAL:
            glib_level = G_LOG_LEVEL_CRITICAL;
            break;
        case Logger::Level::ERROR:
            glib_level = G_LOG_LEVEL_ERROR;
            break;
        }
        g_log(_domain.empty() ? nullptr : _domain.c_str(),
              glib_level, "%s", message.c_str());
    }
}

} // namespace util

} // namespace unity
