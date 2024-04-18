/*Schreiben Sie als C-Programm Ihre eigene “Midi-Shell“, die andere Programme ausführen
kann.
Ihre Midi-Shell soll nach dem Start den Pfad des aktuellen Verzeichnisses, der für Ihre Midi-
Shell gilt, anzeigen. Anschließend wird ein Prompt ausgegeben, der anzeigt, dass die Midi-
Shell Benutzereingaben erwartet. Nach Eingabe eines Programmnamens und zugehöriger
Kommandozeilenparameter soll der entsprechende Prozess gestartet und auf das Ende des
gestarteten Kindprozesses gewartet werden. Danach gibt die Midi-Shell wieder einen Prompt
aus und wartet auf die Eingabe weiterer Befehle, bis durch Eingabe der Zeichenkette
schluss die Shell beendet wird.
Programme, deren Pfad explizit angegeben ist, also mit "/", "./" oder "../" beginnt, können
unmittelbar ausgeführt werden. Für Programmaufrufe ohne Pfadangabe muss der absolute
Pfad durch Durchsuchen des Verzeichnisbaums entsprechend des Inhalts der PATH-
Umgebungsvariablen erst ermittelt werden.
Achten Sie darauf, dass auch Kommandozeilenparameter übergeben werden können!
Stützen Sie sich bei Ihrer Lösung NICHT auf einen exec-Aufruf mit "p" am Ende (z.B.
execvp()), da dieser die Aufgabe automatisch lösen würde.
Die Nutzung der Systemfunktion system() ist VERBOTEN!
*/

#include <linux/limits.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>

const int MAX_USER_INPUT = 64;

int main(int argc, char* argv[]){
	
	// output current working directory
	char cwd_buffer[PATH_MAX];
	if (getcwd(cwd_buffer, sizeof(cwd_buffer)) == NULL){
		printf("Could not get current working directory, therefore aborting execution...\n");
		return -1;
	}

	while (1) {
		
		printf("%s : ", cwd_buffer);
		char user_input[MAX_USER_INPUT];

		fgets(user_input, MAX_USER_INPUT, stdin);
		
		// format user input
		user_input[strcspn(user_input, "\n")] = '\0'; // remove trailing new line
		char
		
		// check if user wants to cancel with "schluss"
		if (strcmp(user_input, "schluss") == 0){
			printf("Midi Shell was aborted!\n");
			return 0;
		}

		// now fork a new child process to execute program
		int child_pid = fork();

		if (child_pid < 0){
			printf("Child process could not be forked, aborting program...\n");
			return -1;
		}
		else if (child_pid == 0){ // code for child process
			execv(user_input, )
		}
		else{ // code for parent process

		}

		printf("User input is : %s\n", user_input);
	}

	return 0;
}
