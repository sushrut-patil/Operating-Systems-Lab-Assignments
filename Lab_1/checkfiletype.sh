#!/bin/bash
#program to echo type and permissions of given file

filename=$1

# Check if the file exists
if [ ! -e $filename ] 
then
    echo "Error: File '$filename' does not exist"
    exit 1
fi

filetype=$(file -b "$filename")
echo "File type: $filetype"


permissions=$(ls -l "$filename" | cut -d ' ' -f 1)
echo "File permissions: $permissions"
