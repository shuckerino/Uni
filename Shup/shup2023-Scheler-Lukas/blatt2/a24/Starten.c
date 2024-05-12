#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main(int argc, char *argv[]) {
	printf("Diese Loesung wurde erstellt von Lukas Scheler \n");
    pid_t pid;
    int status;

    // Fehler, wenn keine Argumente übergeben wurden
    if (argc < 2) {
        printf("Fehler: Kein Programmname angegeben.\n");
        return 1;
    }

    // Kindprozess erzeugen
    pid = fork();

    if (pid == -1) {
        // Fehler beim Forken
        printf("Fehler beim Forken.\n");
        return 1;
    } else if (pid == 0) {
        // Kindprozess

        // Exec-Systemaufruf
        if (execv(argv[1], argv + 1) == -1) {
            // Fehler beim Exec
            printf("Fehler beim Ausführen von %s.\n", argv[1]);
            return 1;
        }
    } else {
        // Elternprozess

        // Warten auf das Ende des Kindprozesses
        wait(&status);

        // Überprüfen, ob Kindprozess normal beendet wurde
        if (WIFEXITED(status)) {
            printf("Kindprozess mit PID %d beendet, Exit-Status: %d\n", pid, WEXITSTATUS(status));
        } else {
            printf("Kindprozess mit PID %d falsch beendet\n", pid);
        }
    }

    return 0;
}
                
