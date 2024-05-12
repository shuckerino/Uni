#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <signal.h>
#include <sys/wait.h>

int main(int argv, char** argc) {
	printf("Diese Loesung wurde erstellt von Lukas Scheler \n");
    // Prüfen, ob vier Übergabeparameter vorhanden sind
    if(argv != 5) {
        printf("Es müssen vier Übergabeparameter sein \n");
        return -1;
    }

    // Variablen zur Speicherung der Prozess-IDs definieren
    int oldPid = getpid();
    int firstPid;
    int secondPid;
    int thirdPid;

    // Ausgabe der Elternprozess-ID und des ersten Übergabeparameters
    printf("ElternprozessID: %d Übergabeparameter 1: %s \n", oldPid, argc[1]);

    // Erster Kindprozess erstellen
    firstPid = fork();
    if(firstPid == 0) {
        printf("Übergabeparameter %d: %s \n", 2, argc[2]);
        while(1);
    }
    else {
        // Zweiten Kindprozess erstellen
        secondPid = fork();
        if(secondPid == 0) {
            printf("Übergabeparameter %d: %s \n", 3, argc[3]);
            while(1);
        }
        else {
            // Dritten Kindprozess erstellen
            thirdPid = fork();
            if(thirdPid == 0) {
                printf("Übergabeparameter %d: %s \n", 4, argc[4]);
                sleep(1);
                // Dritten Kindprozess beenden
                exit(2);
            }
            else {
                // Elternprozess wartet 2 Sekunden
                sleep(2);
                kill(firstPid, 15); // Wird an ersten Kindprozess gesendet
                kill(secondPid, 9); // Wird an zweiten Kindprozess gesendet
                kill(thirdPid, 9); // Wird an dritten Kindprozess gesendet
                // Status der Kindprozesse anzeigen
                printf("Erster Kindprozess: %d \n", wait(&firstPid));
                printf("Zweites Kindprozess: %d \n", wait(&secondPid));
                printf("Drittes Kindprozess: %d \n", wait(&thirdPid));
            }
        }
    }
    return 0;
}
