if [ "$#" = "0" ]
then
	echo "You need to pass an path that should be splitted"
	exit 1
fi
path_part="$(dirname "$1")"
file_part="$(basename "$1")"
file_name_without_extension="${file_part%.*}"
extension="${file_part##*.}"

if [ "$1" == "$extension" ]
then
	extension="$file_name_without_extension"
fi

echo "Zu zerlegender Pfadname: $1"
echo "Pfadanteil: $(dirname "$1")"
echo "Dateianteil: $(basename "$1")"
echo "Dateiname ohne Erweiterung: $file_name_without_extension"
echo "Erweiterung: $extension"
