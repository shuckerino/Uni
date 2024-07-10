#!/bin/bash

file="$1"
# Check if filename was passed
if [ $# = "0" ]
then
	echo "Bitte Dateinamen übergeben"
	exit 1
elif ! [ -f "$file" ]
then
	echo "Die angegebene Datei existiert nicht"
	exit 1
elif ! [ -r "$file" ]
then
	echo "Die angegebene Datei kann nicht gelesen werden"
	exit 1
fi

echo "Inhalt der Datei:"
cat $file

echo "Anzahl der Zeilen der Datei '$file': $(wc -l "$file")"

# Create new filename
file_base=$(basename "$file")
new_file="${file_base}-new.txt"

if [ -f $new_file ]
then
	echo Neue Datei existiert bereits und wird überschrieben
	rm $new_file
	touch $new_file
fi

# Print names numbered
count=1
while read name surname
do
	line="${count}. ${surname} ${name}"
	echo $line
	echo $surname $name >> $new_file
	((count = count + 1))
done < $file

# Write names into new file



