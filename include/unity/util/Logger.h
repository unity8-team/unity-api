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

#include <glib.h>

#include <sstream>
#include <string>

namespace unity
{

namespace util
{

    class Logger
    {
    public:
        enum class Level {
            UNKNOWN = -1,
            DEBUG,
            WARNING,
            CRITICAL,
            ERROR
        };

        Logger(Level level)
            : _level(level),
            _space(true),
            _stream("") {
        }

        ~Logger() {
            // Strip the ending space char if it exists
            auto result = _stream.str();
            if (result.rfind(' ') == std::string::npos) {
                result.pop_back();
            }

            // Write the log
            log(result);
        }

        static inline const char* log_level_string(Level level)
        {
            switch (level) {
            case Level::DEBUG:
                return "DEBUG";
                break;
            case Level::WARNING:
                return "WARNING";
                break;
            case Level::CRITICAL:
                return "CRITICAL";
                break;
            case Level::ERROR:
                return "ERROR";
                break;
            default:
                return "UNKNOWN";
            }
        }

        inline void log(const std::string& message)
        {
            switch (_level) {
            case Level::DEBUG:
                g_debug("%s", message.c_str());
                break;
            case Level::WARNING:
                g_warning("%s", message.c_str());
                break;
            case Level::CRITICAL:
                g_critical("%s", message.c_str());
                break;
            case Level::ERROR:
                g_error("%s", message.c_str());
                break;
            default:
                g_message("%s", message.c_str());
                break;
            }
        }


        inline Logger& no_space() { return *this; }
        inline Logger& maybe_space() {
            if (_space) {
                _stream << ' ';
            }
            return *this;
        }

        inline Logger& operator<<(Level l) {
            _stream << log_level_string(l);

            return maybe_space();
        }

        inline Logger& operator<<(bool b) {
            _stream << (b ? "true" : "false");

            return maybe_space();
        }

        inline Logger& operator<<(char c) {
            _stream << c;

            return maybe_space();
        }

        inline Logger& operator<<(const char *s) {
            _stream << s;

            return maybe_space();
        }

        inline Logger& operator<<(const std::string& s) {
            _stream << s;

            return maybe_space();
        }

        inline Logger& operator<<(const void *p) {
            _stream << ((p == NULL) ? "(null)" : p);

            return maybe_space();
        }

        inline Logger& operator<<(std::nullptr_t) {
            _stream << "(nullptr)";

            return maybe_space();
        }

        inline Logger& operator<<(int t) {
            _stream << t;
            return maybe_space();
        }

        inline Logger& operator<<(long t) {
            _stream << t;
            return maybe_space();
        }

        inline Logger& operator<<(long long t) {
            _stream << t;
            return maybe_space();
        }

        inline Logger& operator<<(unsigned int t) {
            _stream << t;
            return maybe_space();
        }

        inline Logger& operator<<(unsigned long t) {
            _stream << t;
            return maybe_space();
        }

        inline Logger& operator<<(unsigned long long t) {
            _stream << t;
            return maybe_space();
        }

        inline Logger& operator<<(float f) {
            _stream << f;
            return maybe_space();
        }

        inline Logger& operator<<(double d) {
            _stream << d;
            return maybe_space();
        }

    private:
        Level _level;
        bool _space;
        std::ostringstream _stream;
    };

// These are the APIs to be used for logging.
#define debug() Logger(Logger::Level::DEBUG)
#define warn() Logger(Logger::Level::WARNING)
#define critical() Logger(Logger::Level::CRITICAL)
#define error() Logger(Logger::Level::ERROR)

} // namespace util

} // namespace unity
