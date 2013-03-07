#! /usr/bin/env python

#
# Copyright (C) 2012 Canonical Ltd
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

# Report a file in a directory of .gcov reports if the file has uncovered source lines or a
# a number of uncovered source lines that differs from the expected number.
#

import argparse
import collections
import os
import sys
import re
import string

progname = sys.argv[0]

#
# Write the supplied message to the specified stream, followed by a newline.
#
def error(stream, msg):
    print >> stream, progname + ": " + msg

class ParseError(Exception):
    def __init__(self, value):
        self.value = value
    def __str__(self):
        return repr(self.value)

#
# Read the suppressions file. Each line is expected to contain a file name and the expected
# number of uncovered source lines in that file, separated by whitespace. Return a dictionary
# with the expected count for each file.
#

def read_suppressions(suppressions):
    if suppressions != "":
        errors = 0
        line_num = 0
        with open(suppressions, 'rt') as file:
            empty_pat = re.compile(r'(^\s*$)|(^\s*#.*$)');            # Empty line or comment
            good_pat = re.compile(r'\s*(\S+)\s+(\d+)(\s+(#.*)?)?');   # <path> <count> [# comment]
            for line in file:
                line_num += 1
                if empty_pat.match(line):
                    continue
                match = good_pat.match(line)
                if not match:
                    error(sys.stderr, suppressions + ":" + str(line_num) + ": syntax error")
                    errors += 1
                    continue
                name, num = match.group(1, 2)
                yield name, int(num)
    if errors != 0:
        raise ParseError(errors)

#
# Report a file that has an unexpected number of uncovered source lines.
#

def report(file, count, expected_count):
    msg = file + ": " + str(count) + " uncovered source line"
    if count != 1:
        msg += "s"
    if expected_count != 0:
        msg = msg + " (expected " + str(expected_count) + " line"
        if expected_count != 1:
            msg = msg + "s"
        msg += ")"
    error(sys.stdout, msg)

#
# Scan the files in gcovs (which are in directory dir) for uncoverred lines flagged by gcov.
# Report each file that has non-zero uncovered lines (if that file does not appear in the
# suppressions file) and each file with a number of uncovered lines that differs from the
# the expected number.
#

def test_files(dir, gcovs, suppressions):
    counts = dict(read_suppressions(suppressions))
    pat = re.compile(r'(#####|=====):')
    errs = 0

    for g in gcovs:
        # Count the number of lines that contain #####:
        #
        file = os.path.join(dir, g)
        with open(file, "rt") as text:
            count = 0
            for line in text:
                if pat.search(line):
                    count += 1

        # Complain if the expected number doesn't match the actual number or, for files
        # without an expected number, if the count is non-zero.
        #
        if g in counts:
            expected_count = counts[g]
            if expected_count == 0:
                error(sys.stderr, "warning: redundant entry in " + suppressions + ": " + g + " 0");
            if count != expected_count:
                errs += 1
                report(g, count, expected_count)
        else:
            if count != 0:
                errs += 1
                report(g, count, 0)

    # Report each file with uncovered souce lines.
    #
    if errs != 0:
        msg = str(errs) + " file"
        if errs != 1:
            msg += "s"
        msg += " contain"
        if errs == 1:
            msg += "s"
        msg += " unexpected uncovered source lines"
        error(sys.stdout, msg)
        sys.exit(1)

#
# Main program.
#

#
# Parse arguments.
#
parser = argparse.ArgumentParser(description = 'Flag any files that have unexpected non-covered source lines')
parser.add_argument('dir', nargs = 1, help = 'The directory to look for files ending in ".gcov"')
parser.add_argument('-i', '--include-dir', default="",
                    help = 'Only include files underneath this directory are included in the test')
parser.add_argument('suppressions', nargs = '?', default="",
                    help = 'Suppressions file containing lines with the file name and the expected number of uncovered source lines (separated by white space)')
args = parser.parse_args()
progname = parser.prog

#
# Find all the .cpp.gcov files in the specified directory that do not contain "*_test.cpp.gcov" and put
# them into sources, and all the .h.gcov files and put them in headers.
#
dir = args.dir[0]
try:
    files = os.listdir(dir)
except OSError as e:
    msg = "cannot open \"" + dir + "\": " + e.strerror
    error(sys.stderr, msg)
    sys.exit(1)
src_pat = re.compile(r'.+(?<!_test)\.cpp\.gcov$')
hdr_pat = re.compile(r'.+\.h\.gcov$')
sources = [f for f in files if src_pat.match(f)]
headers = [f for f in files if hdr_pat.match(f)]

#
# If an include dir was specified, find all the files ending in ".h" that appear
# in the include dir (recursively).
#
hdr_dir = args.include_dir
includes = []
if hdr_dir != "":
    hdr_pat = re.compile(r'.+\.h$')
    for top, dirs, files in os.walk(hdr_dir):
        for f in files:
            if hdr_pat.match(f):
                includes.append(f + '.gcov')

#
# Remove all the files in headers that don't end in a suffix in includes.
#
strip_pat = re.compile("(?:%s)" % "|".join(map(re.escape, includes)))
headers = [h for h in headers if strip_pat.search(h)]

#
# Remove all the files in headers that contain "_test.cpp.gcda", otherwise we end up generating non-coverage
# complaints for these headers when they are included in a test harness. However, we keep the header if the
# test harness name matches the header, such as for "Point_test.cpp" and "Point.h"; in this case, the
# test harness explicitly tests the header, so we want coverage for that header. We also keep the header
# if the header ends in "Impl" and the test harness matches the header, for example, Runtime_test.cpp and
# RuntimeImpl.h.
#
strip_pat = re.compile(r'(.+)(_test)?\.cpp\.gcda##\1(Impl)?\.h\.gcov')
headers = [h for h in headers if strip_pat.search(h)]

#
# Process the list of sources and headers to look for an unexpected number of uncovered lines in each file.
#
try:
    test_files(dir, sources + headers, args.suppressions)
except OSError:
    sys.exit(1)    # Errors were written earlier
except ParseError:
    sys.exit(1)    # Errors were written earlier

sys.exit    # All went well
