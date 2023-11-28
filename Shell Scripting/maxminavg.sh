#!/bin/bash

#program to find Max,Min digit and Avg of digits of given number.

if [ $# -ne 1 ]
then
	echo "Incorrect Number of Arguments/No Arguments Given"
	exit 1
fi
n=$1
sum=0
i=0
array=()
while [ $n -gt 0 ]
do
	d=$(expr $n % 10)
	array+=($d)
	sum=$(expr $sum + $d)
	n=$(expr $n / 10)
	i=$(expr $i + 1)
	
done

Avg=$(echo "scale=2; $sum/$i" | bc)
echo "The Average of Digits of  ${1}  is  ${Avg}"

Max=0
Min=9
for i in ${array[@]}
do	
	if [ $i -lt $Min ]
		then
		Min=$i
	fi
	if [ $i -gt $Max ]
		then
		Max=$i
	fi
done
echo "The Max value of Digits is  ${Max}"
echo "The Min value of Digits is  ${Min}"


















