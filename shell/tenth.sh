#!/bin/bash
index=1
for line in `cat file.txt`
do
    if [ $index == 10 ]
    then
        echo $line
    fi
    index=`expr $index + 1`
done
