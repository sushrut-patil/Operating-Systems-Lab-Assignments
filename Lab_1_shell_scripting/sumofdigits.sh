#!/bin/bash
#program to count sum of digits of given number

if [ $# -ne 1 ]
then
	echo "Incorrect Number of Arguments/No Arguments Given"
	exit 1
fi
n=$1
sum=0

while [ $n -gt 0 ]
do
	d=$(($n % 10))
	sum=$(expr $sum + $d)
	n=$(expr $n / 10)
done

echo $sum
