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

#include <unity/util/Logger.h>

#include <glib.h>
#include <gtest/gtest.h>
#include <unistd.h>

using namespace unity::util;

namespace {

class LoggerTest : public ::testing::Test
{
public:
    LoggerTest()
    {
        _handler_id = g_log_set_handler(G_LOG_DOMAIN, G_LOG_LEVEL_DEBUG,
                                        _log_handler, this);
        std::cerr << "Set up handler: " << _handler_id << std::endl;
    }

    virtual ~LoggerTest()
    {
        if (_handler_id != 0) {
            g_log_remove_handler(G_LOG_DOMAIN, _handler_id);
        }
    }

    std::string str()
    {
        return _stream.str();
    }

private:
    static void _log_handler(const gchar*, GLogLevelFlags,
                             const gchar* message, gpointer gthis)
    {
        static_cast<LoggerTest*>(gthis)->log_message(message);
    }

    void log_message(const char* message)
    {
        std::cerr << "Message: " << message << std::endl;
        _stream << message;
        usleep(200);
    }

    std::ostringstream _stream;
    guint _handler_id;
};

TEST_F(LoggerTest, testDebug)
{
    auto expected = "Some data about things happening.";
    debug() << expected;
    ASSERT_STREQ(expected, str().c_str());
}

TEST_F(LoggerTest, testInfo)
{
    auto expected = "Some info.";
    info() << expected;
    ASSERT_STREQ(expected, str().c_str());
}

TEST_F(LoggerTest, testWarning)
{
    auto expected = "This shouldn't normally happen.";
    warn() << expected;
    ASSERT_STREQ(expected, str().c_str());
}

TEST_F(LoggerTest, testCritical)
{
    auto expected = "Critical fail.";
    critical() << expected;
    ASSERT_STREQ(expected, str().c_str());
}

TEST_F(LoggerTest, testError)
{
    auto expected = "Error crash.";
    ASSERT_EXIT({error() << expected;},
                ::testing::KilledBySignal(SIGTRAP), expected);
    ASSERT_STREQ(expected, str().c_str());
}

} // namespace
