#!/bin/bash

echo "$0 gestartet am $(date)"

if [ $# -gt 1 ]
then
	echo "Nur ein Argument erlaubt!"
	exit 1
fi

file_name="$1"

if [ ! -f $file_name ]
then
	echo "Argument ist kein Name einer Datei!"
	exit 1
elif [ ! -e $file_name ]
then
	echo "Datei existiert nicht!"
	exit 1
fi

while read -d " " x
do
	echo "$x"
done < $file_name

