#!/bin/bash

echo "Das Skript $0 wurde mit $# Aufrufparametern aufgerufen"

echo "Die Aufrufparameter sind: "

counter=1

for var in "$@"
do
	echo "$counter. Aufrufargument ist: $var"

	# Check if file
	if [ -f "$var" ] 
	then
		echo "'$var' ist eine reguläre Datei" 
	fi

	# Check if directory
	if [ -d "$var" ] 
	then
		echo "'$var' ist ein Verzeichnis"
	fi

	# Check if symbolic link
	if [ -h "$var" ] 
	then
		echo "'$var' ist ein symbolischer Link"
	fi

	counter=`expr $counter + 1`
done
