#!/bin/bash
if [ $# -ne 2 ]; then
	echo "Usage: $0 binary N"
	exit
fi

bsize=1
poweroftwo=$bsize
N=$2
IFS=
it=0
while [ $bsize -le $N ]; do

	out=`./$1 $N $bsize`
	if [ $bsize -eq 1 ]; then
		echo $out | tail -n 2
	else
		echo $out | tail -n 1
	fi
	
	if [ $(( $it % 2 )) -eq 0 ]; then
		bsize=$(( $poweroftwo * 2 ))
		poweroftwo=$bsize
	else
		bsize=$(( $bsize + $bsize / 2 ))
	fi
	it=$(( $it + 1 ))

done


