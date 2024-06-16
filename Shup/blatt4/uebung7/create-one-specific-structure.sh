if [ "$#" != 2 ]
then
	echo "You need to pass two filenames as arguments"
fi

src_file1="$1"
src_file2="$2"
trg_path="./verzeichnis"
trg_prefix="student"

echo "### Start des Shell-Skripts $0"
echo "Aufrufparameter: Quelldateien Q1=${src_file1}, Q2=${src_file2}"

echo "Bitte Namen des Studenten eingeben: "
read student

echo "Aktuelle Konfiguration:"

echo "Neues Verzeichnis: $trg_path/$trg_prefix-$student"

echo "Quelldatei 1: $src_file1"
echo "Quelldatei 2: $src_file2"

echo "Eingabe von RETURN, um die Struktur zu erstellen. STRG-C, um die Erstellung abzubrechen."

read key

if [ $key = "\n" ]
then
	echo "Pressed RETURN"
fi
