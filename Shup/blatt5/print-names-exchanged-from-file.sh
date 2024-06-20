#!/bin/bash

file="$0"
# Check if filename was passed
if [ $# = "0" ]
then
	echo "Bitte Dateinamen übergeben"
	exit 1
elif ! [ -f "$file" ]
then
	echo "Die angegebene Datei existiert nicht"
	exit 1
fi

echo "Inhalt der Datei:"
cat $file

echo "Anzahl der Zeichen der Datei '$file': '${}'"




