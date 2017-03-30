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

#include <gtest/gtest.h>

#include <sstream>

using namespace unity::util;

namespace {

class LoggerTest : public ::testing::Test
{
public:
    std::streambuf *old_stdout_buf;
    std::stringstream stdout_buffer;
    std::streambuf *old_stderr_buf;
    std::stringstream stderr_buffer;

    virtual void SetUp() override
    {
        // Trap stdout to verify tests.
        old_stdout_buf = std::cout.rdbuf();
        std::cout.rdbuf(stdout_buffer.rdbuf());

        // Trap stderr to verify tests.
        old_stderr_buf = std::cerr.rdbuf();
        std::cerr.rdbuf(stderr_buffer.rdbuf());
    }

    virtual void TearDown() override
    {
        std::cout.rdbuf(old_stdout_buf);
        std::cerr.rdbuf(old_stderr_buf);
    }
};

TEST_F(LoggerTest, testEndingSpace)
{
    warn() << "This ends with a space ";
}

TEST_F(LoggerTest, testDebug)
{
    debug() << "Some data about things happening.";
}

TEST_F(LoggerTest, testWarning)
{
    warn() << "This shouldn't normally happen.";
}

TEST_F(LoggerTest, testCritical)
{
    critical() << "Critical fail.";
}

TEST_F(LoggerTest, testError)
{
    ASSERT_EXIT({error() << "Error crash.";},
                ::testing::KilledBySignal(SIGTRAP), "Error crash.");
}

TEST_F(LoggerTest, testStreamLevelDebug)
{
    debug() << "Level:" << Logger::Level::DEBUG;
}

TEST_F(LoggerTest, testStreamLevelWarning)
{
    debug() << "Level:" << Logger::Level::WARNING;
}

TEST_F(LoggerTest, testStreamLevelCritical)
{
    debug() << "Level:" << Logger::Level::CRITICAL;
}

TEST_F(LoggerTest, testStreamLevelERROR)
{
    debug() << "Level:" << Logger::Level::ERROR;
}

TEST_F(LoggerTest, testStreamLevelUnknown)
{
    debug() << "Level:" << Logger::Level::UNKNOWN;
}

TEST_F(LoggerTest, testStreamBool)
{
    debug() << "Bool:" << true;
}

TEST_F(LoggerTest, testStreamPointer)
{
    debug() << "Pointer:" << this;
}

TEST_F(LoggerTest, testStreamNullPointer)
{
    debug() << "Pointer:" << nullptr;
}

TEST_F(LoggerTest, testStreamInt)
{
    debug() << "Count:" << 42;
}

TEST_F(LoggerTest, testStreamShort)
{
    debug() << "Count:" << (short)42;
}

TEST_F(LoggerTest, testStreamLong)
{
    debug() << "Count:" << (long)42;
}

TEST_F(LoggerTest, testStreamLongLong)
{
    debug() << "Count" << (long long)42;
}

TEST_F(LoggerTest, testStreamUnsignedInt)
{
    debug() << "Unsigned:" << (unsigned int)42;
}

TEST_F(LoggerTest, testStreamUnsignedShort)
{
    debug() << "Unsigned:" << (unsigned short)42;
}

TEST_F(LoggerTest, testStreamUnsignedLong)
{
    debug() << "Unsigned Long:" << (unsigned long)42;
}

TEST_F(LoggerTest, testStreamUnsignedLongLong)
{
    debug() << "Unsigned long long:" << (unsigned long long)42;
}

TEST_F(LoggerTest, testStreamFloat)
{
    debug() << "Float:" << 2.2f;
}

TEST_F(LoggerTest, testStreamDouble)
{
    debug() << "Double:" << (double)2.2f;
}

} // namespace
