#!/bin/bash

RED='\033[0;31m'
GREEN='\033[0;32m'
RESET='\033[0m'
#file to test
file1=./testfiles/sphere_tests.rt
file2=./testfiles/ambiant_tests.rt
file3=./testfiles/camera_tests.rt
file4=./testfiles/cylinder_tests.rt
file5=./testfiles/light_tests.rt
file6=./testfiles/plane_tests.rt

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
inputfile=$file1
   while read -r line; do
    echo $line > temp.txt
    output=$(./minirt  temp.txt)
    if [ "$output" == "OK" ]; then
        echo -e "${GREEN}Test passed${RESET}"
    else
        echo -e "${RED}Test failed${RESET}"
    fi
done < $inputfile

inputfile=$file2
   while read -r line; do
    echo $line > temp.txt
    output=$(./minirt  temp.txt)
    if [ "$output" == "OK" ]; then
        echo -e "${GREEN}Test passed${RESET}"
    else
        echo -e "${RED}Test failed${RESET}"
    fi
done < $inputfile

inputfile=$file3
   while read -r line; do
    echo $line > temp.txt
    output=$(./minirt  temp.txt)
    if [ "$output" == "OK" ]; then
        echo -e "${GREEN}Test passed${RESET}"
    else
        echo -e "${RED}Test failed${RESET}"
    fi
done < $inputfile

inputfile=$file4
   while read -r line; do
    echo $line > temp.txt
    output=$(./minirt  temp.txt)
    if [ "$output" == "OK" ]; then
        echo -e "${GREEN}Test passed${RESET}"
    else
        echo -e "${RED}Test failed${RESET}"
    fi
done < $inputfile

inputfile=$file5
   while read -r line; do
    echo $line > temp.txt
    output=$(./minirt  temp.txt)
    if [ "$output" == "OK" ]; then
        echo -e "${GREEN}Test passed${RESET}"
    else
        echo -e "${RED}Test failed${RESET}"
    fi
done < $inputfile

inputfile=$file6
   while read -r line; do
    echo $line > temp.txt
    output=$(./minirt  temp.txt)
    if [ "$output" == "OK" ]; then
        echo -e "${GREEN}Test passed${RESET}"
    else
        echo -e "${RED}Test failed${RESET}"
    fi
done < $inputfile

rm temp.txt > /dev/null
