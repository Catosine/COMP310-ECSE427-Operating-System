#!/bin/bash

# Test help
echo help > testfile.txt

RANDOME=107

# maximum size of memory
max_mem_size=$1

# maximum size of RAM
max_ram_size=$2

avg_size=$((max_ram_size/3))

script1_size=`shuf -i 1-$avg_size -n 1`
echo $RANDOM

# prepare main file:

idx=0
