#!/usr/bin/python

import fileinput
import re
import sys

# Lines affter 'Entering directory' (make -w) 
# will have the directory path prepended
# This is neccessary when building makefile with SUBTARGETS

DIR_NAME='___'
# Replace the input read from a file (stdin)
# cat ~/temp/make-w_output.txt | ~/temp/make_abs.py
# In order to handle input from stderr:
# make -w 2>&1 | ~/temp/make_abs.py
for line in fileinput.input():
    if line.find("Entering directory")!=-1:
        # print "+++", line
        found = re.search("'\S[0-9A-Za-z/_]+", line)
        # print found
        if found:
            DIR_NAME=found.group(0)[1:] # drop the single quote
    else:
        if line.startswith('../'):
            sys.stdout.write('%s/%s' % (DIR_NAME, line))
        else:
            sys.stdout.write(line)
fileinput.close()