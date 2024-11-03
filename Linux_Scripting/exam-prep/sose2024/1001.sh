#!/bin/bash

touch 1001zeilen.txt

line_count=1

while [ $line_count -le 1001 ]
do
	if [ $line_count -eq 1 ]
	then
		echo "1. Zeile: Eine Datei mit 1001 Zeilen." >> 1001zeilen.txt
	else
		echo $line_count. Zeile: 00$line_count'z' >> 1001zeilen.txt
	fi
	
	line_count=$(expr $line_count + 1)
done
