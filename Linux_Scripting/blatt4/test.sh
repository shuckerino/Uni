echo "Ausführung von $0 mit $# Aufrufparametern"

fctshowfilecontent() {
	file_name=$(basename "$1")
	num_lines=$(wc -l < "$file_name")
	echo "Datei /'${file_name}/' hat $num_lines Zeile/n." 
}

fctshowfilecontent $1
fctshowfilecontent $2
fctshowfilecontent $3

