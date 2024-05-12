#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>

int maxCommandLength;

void display_prompt() {
    // Anzeigen des aktuellen Arbeitsverzeichnisses
    char cwd[maxCommandLength];
    if (getcwd(cwd, sizeof(cwd)) != NULL) {
        printf("Midi-Shell: %s $ ", cwd);
    } else {
        printf("Midi-Shell: $ ");
    }
}

int main() {
	printf("Diese Loesung wurde erstellt von Lukas Scheler \n");
    maxCommandLength = 1024;
    int maxArgs = 64;
    char command[maxCommandLength];
    char *args[maxArgs];
    int num_args;
    int status;

    printf("Midi-Shell started.\n");
    display_prompt();

    while (fgets(command, maxCommandLength, stdin) != NULL) {
        // Entferne newline-Zeichen von der Eingabe
        command[strcspn(command, "\n")] = 0;

        // Überprüfe ob die Eingabe "schluss" ist, um die Shell zu beenden
        if (strcmp(command, "schluss") == 0) {
            printf("Midi-Shell beendet.\n");
            break;
        }

        // Tokenize den Befehl und speichere die Tokens in args
        num_args = 0;
        args[num_args] = strtok(command, " ");
        while (args[num_args] != NULL && num_args < maxArgs - 1) {
            num_args++;
            args[num_args] = strtok(NULL, " ");
        }
        args[num_args] = NULL;

	    // Überprüfe ob der Befehl "cd" ist, um das Verzeichnis zu wechseln
        if (strcmp(args[0], "cd") == 0) {
            if (num_args < 2) {
                printf("Fehler: Pfad fehlt nach \"cd\".\n");
            } else {
                if (chdir(args[1]) != 0) {
                    perror("Fehler beim Wechseln des Verzeichnisses");
                }
            }
            display_prompt();
            continue;
        }

        // Erzeugen eines Kindprozesses
        pid_t pid = fork();
        if (pid < 0) {
            // Fehler beim Erzeugen des Kindprozesses
            perror("Fehler beim Erzeugen des Kindprozesses");
            exit(EXIT_FAILURE);
        } else if (pid == 0) {
            // Kindprozess
            // Überprüfe ob der Befehl mit "/" oder "./" oder "../" beginnt,
            // in dem Fall kann der Befehl direkt ausgeführt werden
            if (args[0][0] == '/' || strncmp(args[0], "./", 2) == 0 || strncmp(args[0], "../", 3) == 0) {
                execv(args[0], args);
            } else {
                // Sonst suche nach dem Befehl im PATH
                char *path = getenv("PATH");
                char *path_copy = strdup(path);
                char *dir = strtok(path_copy, ":");
                while (dir != NULL) {
                    char command_path[maxCommandLength];
                    snprintf(command_path, maxCommandLength, "%s/%s", dir, args[0]);
                    execv(command_path, args);
                    dir = strtok(NULL, ":");
                }
                free(path_copy);
            }

            // Falls execv fehlschlägt, gibt es einen Fehler aus
            perror("Fehler beim Ausführen des Befehls");
            exit(EXIT_FAILURE);
        } else {
            // Elternprozess
            // Warten auf den Kindprozess
            waitpid(pid, &status, 0);
            display_prompt();
        }
    }
    return 0;
}
