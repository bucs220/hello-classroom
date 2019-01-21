#!/bin/bash

# This file is for cloning assignments made in GitHub Classroom into the
# present working directory.

# USAGE
# This script accepts the following command line arguments:
# $1 - the name of the github classroom (e.g. "bucs220")
# $2 - the assignment's prefix before the username MINUS a trailing hyphen (e.g. "F17-A1")
# $3 - the name of the file with a list of repository owners (either individual users or groups).
# $4 - (optional) time in seconds to sleep between requests

# PREREQUISITES
# You must set up your shell to use SSH keys and enable credential caching. See https://help.github.com/articles/caching-your-github-password-in-git/
# The names in the file MUST be one username per line, with a carriage return at end of file

# CREDITS
# Inspired by https://github.com/umasshokie/classroom_scripts

#Check that 3 or 4 parameters are given
if [[ $# -lt 3  || $# -gt 4 ]];
then
	echo "Usage: source classroom-clone.sh CLASSROOM ASSIGNMENT NAMES [SLEEP]"
else
	if [[ $# -ge 4 ]]; then
		t=$4
	else
		t=0
	fi

	#set parameters to more obvious variable names
	classroom="git@github.com:"$1"/"
	assignment=$2
	file=$3

	# read line by line and clone the assignment
	while read line
	do
		name=${assignment}-${line}
		git clone ${classroom}${name}
		sleep ${t}
	done < $file
fi
