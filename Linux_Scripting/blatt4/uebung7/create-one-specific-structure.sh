if [ "$#" != 2 ]
then
	echo "You need to pass two filenames as arguments"
fi

src_file1="$1"
src_file2="$2"
trg_path="./verwaltung"
trg_prefix="student"

echo "### Start des Shell-Skripts $0"
echo "Aufrufparameter: Quelldateien Q1=${src_file1}, Q2=${src_file2}"

echo "Bitte Namen des Studenten eingeben: "
read student

echo "Aktuelle Konfiguration:"

new_user_dir="$trg_path/$trg_prefix-$student"
new_file1_name=""
echo "Neues Verzeichnis: $new_user_dir"

echo "Quelldatei 1: $src_file1"
echo "Quelldatei 2: $src_file2"

echo "Eingabe von RETURN, um die Struktur zu erstellen. STRG-C oder irgendeine andere Eingabe, um die Erstellung abzubrechen."

read key

if [ "$key" != "" ]
then
	echo "You did not press RETURN only, so the script will terminate here..."
	exit 1
fi

# User wants to continue to create the structure
echo "Erstelle Verzeichnis $new_user_dir"


echo "Erstelle Datei $src_file1 in $new_user_dir"


echo 
