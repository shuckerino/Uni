#!/bin/bash

echo "Using bash as shell interpreter"

echo "Printing all args in one line:"
echo "$@"

echo "Printing all args in separate lines indexed:"

idx=1
for arg in "$@"
do
	echo "${idx}-ter Aufrufparameter: $arg"
	((idx++))
done
