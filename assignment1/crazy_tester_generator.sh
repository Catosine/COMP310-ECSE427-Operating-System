#!/bin/bash

# Test help
echo help > testfile.txt

# maximum size of memory
max_mem_size=$1

idx=0

# fill up the memory
while [ $idx -lt $max_mem_size ]
do
    echo "set $idx hello$idx" >> testfile.txt
    # test blanks
    echo  >> testfile.txt
    echo "print $idx" >> testfile.txt
    idx=$((idx+1))
done

# try to insert new variable to a full memory
echo "set ecse427 comp310" >> testfile.txt

# try to print a variable that does not exist
echo "print ecse427" >> testfile.txt

idx=0

# update all memory
while [ $idx -lt $max_mem_size ]
do
    echo "set $idx world$idx" >> testfile.txt
    echo "print $idx" >> testfile.txt
    idx=$((idx+1))
done

# illegal set command: no value
echo "set 1" >> testfile.txt
echo "print 1" >> testfile.txt

# illegal set command: lots of blanks as value
echo "set 1                 " >> testfile.txt
echo "print 1" >> testfile.txt

# illegal set command: multiple values (either to be rejected or only the first one is acceptable)
echo "set 1 hello world" >> testfile.txt
echo "print 1" >> testfile.txt

# naughty set: with lots of blanks
echo "             set             1    hahahah          " >> testfile.txt
echo "print 1" >> testfile.txt

# illegal prints: no variable
echo "print" >> testfile.txt

# illegal prints: variable does not exist
echo "print mcgill" >> testfile.txt

# illegal prints: variable as blanks
echo "print                 " >> testfile.txt

# naughty prints: a lots of blanks
echo "                 print                1       " >> testfile.txt

# illegal run: no script.txt
echo "run" >> testfile.txt

# illegal run: blanks as script.txt
echo "run           " >> testfile.txt

# illegal run: script is not .txt
touch lalalalalala.abcd
rm lalalalalala.abcd
echo "run lalalalalala.abcd" >> testfile.txt

# run: ok
touch a_very_nice_file.txt
echo "help" >> a_very_nice_file.txt
echo "run a_very_nice_file.txt" >> testfile.txt

# naughty run: run with lots of blanks
echo "                 run                   a_very_nice_file.txt             " >> testfile.txt

# illegal run: script does not exist
echo "run a_very_bad_file.txt" >> testfile.txt

# unsupported command
echo "super_artificial_intelligence" >> testfile.txt

# Test quit
echo quit >> testfile.txt

# finish
echo done

./mysh < testfile.txt

rm a_very_nice_file.txt