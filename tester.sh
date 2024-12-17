#!/bin/bash

RED='\033[0;31m'
GREEN='\033[0;32m'
RESET='\033[0m'
#check if the program is compiled
if [ ! -f "minirt" ]; then
    make > /dev/null
    make clean > /dev/null
fi

inputfile=$1
while read -r line; do
    echo $line > temp.txt
    output=$(./minirt  temp.txt)
    if [ "$output" == "OK" ]; then
        echo -e "${RED}Test shouldńt pass${RESET}"
        # break
    fi
done < $inputfile
rm temp.txt > /dev/null
