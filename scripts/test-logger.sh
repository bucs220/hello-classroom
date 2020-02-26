#!/usr/bin/bash
# //=== scripts/test-logger.sh - artifact logging -*- Bash -*-===//
# //
# // \date 2020
# // \author Matthew Cole
# // \copyright GNU General Public License v3.0 or later
# // SPDX-License-Identifier: GPL-3.0-or-later
# //
# // This program is free software: you can redistribute it and/or modify
# // it under the terms of the GNU General Public License as published by
# // the Free Software Foundation, either version 3 of the License, or
# // (at your option) any later version.
# //
# // This program is distributed in the hope that it will be useful,
# // but WITHOUT ANY WARRANTY; without even the implied warranty of
# // MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# // GNU General Public License for more details.
# //
# // You should have received a copy of the GNU General Public License
# // along with this program.  If not, see <https://www.gnu.org/licenses/>
# //
# //===----------------------------------------------------------------------===//
# ///
# /// \file 
# /// This script generates a log artifact after running the test executable.
# ///
# /// \brief
# /// The log file contains the tester's username, the test platform's hostname,
# /// the test date and time, and the console output from the test executable.
# /// Each successive run of test-logger.sh appends output creating a persistent
# /// artifact for grading purposes.
# ///
# //===----------------------------------------------------------------------===//

# Collect execution environment/user information
DATE="$(date)"
TESTER="$(whoami)"
HOSTNAME="$(hostname)"
echo "Tested by ${TESTER} on ${HOSTNAME} at ${DATE}" | tee -a results.log

# Collect a starting timestamp
START=$(date +%s%N)

# Build and test
make -k test 2>&1 | tee -a results.log
./test 2>&1 | tee -a results.log
echo | tee -a results.log

# Log finishing time
echo "Run complete at $((($(date +%s%N) - $START)/1000000000))s" | tee -a results.log