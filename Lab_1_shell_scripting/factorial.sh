#!/bin/bash

#program to find factorial of number using recursion

fact() {
	
	if [ $1 -eq 0 ]
	then
		echo 1
	else
		echo $(($1 * $(fact $(( $1 - 1 )))))
		
	fi
}

echo $(fact $1)
