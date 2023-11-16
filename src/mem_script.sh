#!/bin/bash

valgrind ./test 2>log.txt
lost=$(cat log.txt | grep lost | grep "0 bytes" -v)
rm log.txt
if [[ $lost =~ ^$ ]]
then
echo -e "\e[0;32m\t MEM RESULT: SUCCESS\e[0m"
else
echo -e "\e[0;31m\t MEM RESULT: FAILURE\e[0m"
fi