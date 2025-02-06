#!/bin/bash

if [[ $# -lt 1 ]]; then
	echo need binary
	exit
fi

first=1
for KB in 2 4 8 16 32 64 128 256 512 1024 2048 4096 8192 16384 32756
do
	oldIFS=$IFS
	IFS=;
	out=`./$1 $(($KB * 1024))`
	if [ $first -eq 1 ]; then
		echo $out
	else
		echo $out | tail -n 1
	fi
	first=0
	IFS=$oldIFS
done
