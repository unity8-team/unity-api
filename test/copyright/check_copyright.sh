#!/bin/sh

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
# Check that, somewhere in the first 30 lines of each file, the string "Copyright" (case independent) appears.
# Print out a messsage for each file without a copyright notice and exit with non-zero status
# if any such file is found.
#

usage()
{
    echo "usage: check_copyright dir [ignore_dir]" >&2
    exit 2
}

[ $# -lt 1 ] && usage
[ $# -gt 2 ] && usage

ignore="grep -v CMakeFile"

[ $# -eq 2 ] && {
    ignore="$ignore | grep -v \"$2\""
}

err=no
for file in `find "$1" \
    -name '*.cpp' -o \
    -name '*.h' -o \
    -name '*.py' -o \
    -name '*.sh' -o \
    -name 'CMakeLists.txt' -o \
    -name '*.cmake'  \
    | grep -v CMakeFiles \
    | eval $ignore`
do
    head -30 "$file" | grep -q -i Copyright
    [ $? -ne 0 ] && {
        echo "$file: no copyright header"
        err=yes
    }
done

[ $err = yes ] && exit 1

exit 0
