#!/usr/bin/sh

echo "Start von Shell-Skript $0 am `date`"
echo "Die Prozess-ID des Shell-Skripts lautet: $$"
echo "Shell-Skript wird aufgeführt von: $USER"
echo "Das aktuelle Arbeitsverzeichnis ist: $PWD"
echo "Das Home-Verzeichnis des aktuellen Benutzers ist: $HOME"
echo "Die Pfadvariable hat den Wert: $PATH"
echo "Der Rechner ist: ($HOSTNAME)"
echo "Das installierte System ist: `uname -a`"
echo "Die verwendete Shell ist: $SHELL"
echo "Das Terminal ist: $TERM"
echo "Ende von Shell-Skript $0 am `date`"
