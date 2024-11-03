#!/bin/bash

echo "Shell-Skript $0 wird ausgeführt und hat $# Aufrufparameter"

function fctshowfilecontent () {
	
	local file="$1"
	num_lines=$(wc -l "$file")
	echo "Datei $file hat $num_lines Zeile(n)."

	echo "Inhalt:"

	echo $(cat "$file")
}


fctshowfilecontent "$1"
fctshowfilecontent "$2"
fctshowfilecontent "$3"
