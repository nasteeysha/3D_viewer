#!/bin/bash

while true; do
  read -r -p "Linux(windows) or Mac? (L/M): " ANSWER
    case $ANSWER in
      [Ll]* ) ../build/viewer; break;;
      [Mm]* ) ../build/*/viewer; break;;
      * ) echo "Please answer L or M.";;
    esac
done