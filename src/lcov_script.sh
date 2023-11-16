#!/bin/bash

lcov -t "test" -o test.info -c -d . 2>log.txt 1>log.txt
rm log.txt
genhtml -o report test.info | grep -e "lines" -e "functions"
./show.sh