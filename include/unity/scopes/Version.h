//
// DO NOT EDIT Version.h (this file)! It is generated from Version.h.cmake.
//

/*
 * Copyright (C) 2013 Canonical Ltd
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 3 as
 * published by the Free Software Foundation.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 *
 * Authored by: Michi Henning <michi.henning@canonical.com>
 */

#ifndef UNITY_SCOPES_VERSION_H
#define UNITY_SCOPES_VERSION_H

#define UNITY_SCOPES_VERSION_MAJOR 0
#define UNITY_SCOPES_VERSION_MINOR 1
#define UNITY_SCOPES_VERSION_MICRO 0

#define UNITY_SCOPES_VERSION_STRING "0.1.0"

namespace unity
{

namespace scopes
{

/**
\brief Class to obtain version information for the Scopes API at run time.

Version information is represented as
<i>&lt;<code>major</code>&gt;</i>.<i>&lt;<code>minor</code>&gt;</i>.<i>&lt;<code>micro</code>&gt;</i>.

Releases that differ in the major or minor version number are binary incompatible.

Releases of the library that differ only in the micro version number are binary compatible with older releases,
so client code does not need to be recompiled to use the newer library version.

A different minor version is compatible at the API level, that is, it may add new APIs, but does not change existing
ones. API clients must be recompiled for a new major version.

A different major version indicates incompatible API changes.
*/

// Version could be a namespace instead of a class, but that requires a lower-case name,
// which is inconsistent with the remainder of the API.

class Version
{
public:
    /**
    \return The major version number.
    */
    static int major_version();

    /**
    \return The minor version number.
    */
    static int minor_version();

    /**
    \return The micro version number.
    */
    static int micro_version();

    /**
    \return The version string in the format
            <i>&lt;<code>major</code>&gt;</i>.<i>&lt;<code>minor</code>&gt;</i>.<i>&lt;<code>micro</code>&gt;</i>.
    */
    static const char* str();    // Returns "major.minor.micro"

    // TODO: Add methods to report compiler version and compiler flags

private:
    Version() = delete;
    ~Version() = delete;
};

} // namespace scopes

} // namespace unity

#endif
