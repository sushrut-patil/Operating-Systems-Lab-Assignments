#!/bin/bash
#program to check if given string is palindrome
string=$1


reverse=$(echo "$string" | rev)

if [ $string == $reverse ] 
then
    echo "The string '$1' is a palindrome"
else
    echo "The string '$1' is not a palindrome"
fi
