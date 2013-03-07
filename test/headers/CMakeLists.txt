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

#
# Test that all header files compile stand-alone and that no public header includes an internal one.
#

set(root_inc_dir ${CMAKE_SOURCE_DIR}/include)

set(subdirs
    unity
    unity/scopes
    unity/util
)

foreach(dir ${subdirs})

    string(REPLACE "/" "-" location ${dir})

    set(public_inc_dir ${root_inc_dir}/${dir})
    set(internal_inc_dir ${public_inc_dir}/internal)

    # Test that each public header compiles stand-alone.
    add_test(stand-alone-${location}-headers
        ${CMAKE_CURRENT_SOURCE_DIR}/compile_headers.py -v
            ${public_inc_dir} ${CMAKE_CXX_COMPILER} "-I${root_inc_dir} -I${public_inc_dir} ${CMAKE_CXX_FLAGS}")

    # Test that each internal header compiles stand-alone.
    add_test(stand-alone-${location}-internal-headers
        ${CMAKE_CURRENT_SOURCE_DIR}/compile_headers.py -v
            ${internal_inc_dir} ${CMAKE_CXX_COMPILER} "-I${root_inc_dir} -I${internal_inc_dir} ${CMAKE_CXX_FLAGS}")

    # Test that no public header includes an internal header
    add_test(clean-public-${location}-headers ${CMAKE_CURRENT_SOURCE_DIR}/check_public_headers.py ${public_inc_dir})

endforeach(dir)
