#
# Copyright (C) 2013 Canonical Ltd
#
# This program is free software: you can redistribute it and/or modify
# it under the terms of the GNU General Public License version 3 as
# published by the Free Software Foundation.
#
# This program is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.
#
# You should have received a copy of the GNU General Public License
# along with this program.  If not, see <http://www.gnu.org/licenses/>.
#
# Authored by: Michi Henning <michi.henning@canonical.com>
#

set(UNITY_SRC
    Exception.cpp
    UnityExceptions.cpp
)

set(UNITY_INTERNAL_SRC
    internal/ExceptionImpl.cpp
    internal/UnityExceptionsImpl.cpp
)

set(UTIL_SRC
    util/Daemon.cpp
    util/FileIO.cpp
)

set(UTIL_INTERNAL_SRC
    util/internal/DaemonImpl.cpp
)

set(SCOPES_SRC
    scopes/Version.cpp
)

set(SCOPES_INTERNAL_SRC
)

set(SCOPES_LIB_SRC
    ${UNITY_SRC}
    ${UNITY_INTERNAL_SRC}
    ${UTIL_SRC}
    ${UTIL_INTERNAL_SRC}
    ${SCOPES_SRC}
    ${SCOPES_INTERNAL_SRC}
)

add_library(${SCOPES_LIB} SHARED ${SCOPES_LIB_SRC})

install(TARGETS ${SCOPES_LIB} LIBRARY DESTINATION lib)
