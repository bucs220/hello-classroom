#!/bin/bash

# This script visits a directory of Github cloned directories and grades them.
# If you want to use it with group assignments, you will need a list of each group name instead of student usernames.
# It requires three command line arguments:
#	1. CLONEDIR - Path to the directory containing the cloned directories.
#	2. GRADEDIR - Path to the directory containing the grading files test.c and test.py
# 3. GRADER - Name of the grader. Will appear in the commit message.

# Author: @colematt, Matthew Cole

#Check that 3 parameters are given:
if [[ $# -ne 3 ]];
then
	echo "Usage: source dir-grade.sh <CLONEDIR> <GRADEDIR> <GRADER>"
  exit 1
else
  REPOS="$1"
  GRADEFILES="$2"
  GRADER="$3"

  let DIRCOUNT=`ls -l ${REPOS} | grep -c ^d`
  let DNUM=0

  for dir in REPOS/*
  do
    if [ -d "${dir}" ] ; then
      let DNUM++
      echo "Processing ${dir} (${DNUM}/${DIRCOUNT}) ..."

      # Copy grading source files
    	cp $GRADEFILES/test.c $GRADEFILES/test.py ${dir}

      # Build process
    	make -C ${dir} test
    	make -C ${dir} test-run
    	rm -fv ${dir}/test.c ${dir}/test.py
    	make really-clean

      # Verify test results were published by make test-run
    	if [ -e ${dir}/test_results.log ]
      then
  	    cat ${dir}/test_results.log
      else
  	    echo "Failed to complete test-run! See ${GRADER}" > test_results.log
  	    cat ${dir}/test_results.log
      fi

      # Commit the grading to the repository
      git -C ${dir} add ${dir}/test_results.log
      git -C ${dir} commit -a -m "Graded by ${GRADER}"
      git -C ${dir} push
    fi
  done
fi
