#!/bin/bash

#program to sort elements of array

read -p "Enter Number of Elements in Array : " N
arr=()
for i in $(seq 1 $N)
do
	read -p "Enter ${i} Number :" num
	arr+=($num)
done

for ((i = 0;i<$N;i++))
do
	for ((j = 0;j<(($N - $i -1));j++))
	do
		if [ ${arr[j]} -gt ${arr[$((j+1))]} ]
		then
			temp=${arr[j]}
            arr[$j]=${arr[$((j+1))]}  
            arr[$((j+1))]=$temp
			echo $temp
		fi
	done
done
echo "Sorted Array : "
echo ${arr[*]}

