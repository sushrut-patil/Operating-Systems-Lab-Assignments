#!/bin/bash
#program to find factorial of number without recursion

N=$1
fact=1
for ((i=1;i<=N;i++))
do
	fact=$(($fact * $i))
done	

echo $fact
