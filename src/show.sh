#!/bin/bash

tmp=1;

while true; do
  read -r -p "Do you wish to open report? (Y/N): " ANSWER
      case $ANSWER in
      [Yy]* ) break;;
      [Nn]* ) (( tmp-=1 )); break;;
      * ) echo "Please answer Y or N.";;
    esac
done
if (( tmp == 1 )); then
  while true; do
    read -r -p "Linux(windows) or Mac? (L/M): " ANSWER
      case $ANSWER in
        [Ll]* ) x-www-browser report/index.html; break;;
        [Mm]* ) open report/index.html; break;;
        * ) echo "Please answer L or M.";;
      esac
  done
fi