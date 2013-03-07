#! /usr/bin/env python

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
# Little helper program to test that public header files don't include internal header files.
#
# Usage: check_public_headers.py directory
#
# The directory specifies the location of the header files. All files in that directory ending in .h (but not
# in subdirectories) are tested.
#

import argparse
import os
import sys
import re

progname = sys.argv[0]

#
# Write the supplied message to the specified stream, followed by a newline.
#
def error(stream, msg):
    print >> stream, progname + ": " + msg + "\n"

#
# For each of the supplied headers, check whether that header includes something in an internal directory.
# Return the count of headers that do this.
#
def test_files(dir, hdrs):
    errs = 0
    for hdr in hdrs:
        try:
            hdr_name = dir + "/" + hdr
            file = open(hdr_name, "r")
        except OSError:
            msg = "cannot open \"" + hdr_name + "\": " + e.strerror
            error(sys.stderr, msg)
            exit(1)

        include_pat = re.compile(r'^#[ \t]*include[ \t]+[<"](.*)[>"]')
        internal_pat = re.compile(r'.*internal/')

        lines = file.readlines()
        line_num = 0
        for l in lines:
            line_num += 1
            include_mo = include_pat.match(l)
            if include_mo:
                header_path = include_mo.group(1)
                internal_mo = internal_pat.match(header_path)
                if internal_mo:
                    errs += 1
                    error(sys.stderr, hdr_name + " includes an internal header at line " + str(line_num) + ": " + header_path)
    return errs

#
# Main program.
#

#
# Parse arguments.
#
parser = argparse.ArgumentParser(description = 'Test that no public header includes an internal header.')
parser.add_argument('dir', nargs = 1, help = 'The directory to look for header files ending in ".h"')
args = parser.parse_args()
progname = parser.prog

#
# Find all the .h files in specified directory and look for #include directives that mention "internal".
#
dir = args.dir[0]
try:
    files = os.listdir(dir)
except OSError as e:
    msg = "cannot open \"" + dir + "\": " + e.strerror
    error(sys.stderr, msg)
    sys.exit(1)
pat = re.compile(r'.+\.h$')
hdrs = [hdr for hdr in files if pat.match(hdr)]

sys.exit(test_files(dir, hdrs))
