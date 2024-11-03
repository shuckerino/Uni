#!/bin/bash

echo "Shell-Skript $0 mit $# Aufrufparametern gestartet!"

cwd=$(pwd)

echo "Aktuelles Arbeitsverzeichnis ist $cwd"

if [[ $cwd == "/home"* ]]
then
	echo "Wir sind im Home-Vezeichnis"
else
	echo "Wir sind NICHT im Home-Verzeichnis"
fi


