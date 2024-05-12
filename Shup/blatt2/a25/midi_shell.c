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
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>

const int MAX_USER_INPUT = 64;

int main()
{
	// fetch current working directory
	char cwd_buffer[PATH_MAX];
	if (getcwd(cwd_buffer, sizeof(cwd_buffer)) == NULL)
	{
		printf("Could not get current working directory, therefore aborting execution...\n");
		return -1;
	}

	while (1) // infinite loop, break only with "schluss"
	{
		// print current working directory
		printf("%s : ", cwd_buffer);

		// get user input (shell command to be executed)
		char user_input[MAX_USER_INPUT];
		fgets(user_input, MAX_USER_INPUT, stdin);

		// format user input (remove trailing new line)
		user_input[strcspn(user_input, "\n")] = '\0';

		// check if user wants to cancel with "schluss"
		if (strcmp(user_input, "schluss") == 0)
		{
			printf("Midi Shell was aborted!\n");
			return 0;
		}

		// tokenize user input (into command, options, arguments etc.)
		char *args[64];
		int argc = 0;
		args[argc] = strtok(user_input, " ");
		while (args[argc] && argc < 63)
		{
			argc++;
			args[argc] = strtok(NULL, " ");
		}

		// if no command entered
		if (argc == 0)
			continue;

		// allocate memory for the full_path
		char *full_path = malloc(128 * sizeof(char));

		// bool indicating, if an executable program was found
		int command_found = 0;

		// if no explicit path, we need to fetch the path variable and look for program in these paths
		if (user_input[0] != '/' && user_input[0] != '.')
		{
			// get entire path variable
			char *path_var = getenv("PATH");
			if (path_var == NULL)
			{
				printf("The path variable could not be fetched, aborting program...\n");
				return -1;
			}

			// make copy of path variable, because string tokenizer is disruptive on original string
			char path_copy[1024];
			strncpy(path_copy, path_var, sizeof(path_copy));
			// printf("Path copy is %s", path_copy);

			// split path variable into paths
			char *path_part = strtok(path_copy, ":");
			while (path_part != NULL)
			{
				// printf("Token: %s\n", path_part);
				//  create full path with sprintf to concatenate to the full path
				sprintf(full_path, "%s/%s", path_part, user_input);
				// printf("Full path is: %s\n", full_path);

				//  check if path exists
				if (access(full_path, X_OK) == 0) // X_OK to check if it is executable
				{
					command_found = 1;
					// printf("Path in Path variable found, right path is %s\n", path_part);
					break;
				}
				path_part = strtok(NULL, ":"); // continue to get the next token
			}
		}

		if (command_found == 1)
		{
			int child_pid = fork();

			if (child_pid < 0)
			{
				printf("Child process could not be forked, aborting program...\n");
				return -1;
			}
			else if (child_pid == 0) // code for child process
			{
				printf("The final path to be executed is: %s", full_path);
				execv(full_path, args);

				perror("Error when executing child program...\n");
			}
			else // code for parent process
			{
				int status;
				wait(&status);
				printf("Child exited with code %d\n", status);
			}
		}
		else
		{
			printf("Command was not found!\n");
		}
	}
	return 0;
}
