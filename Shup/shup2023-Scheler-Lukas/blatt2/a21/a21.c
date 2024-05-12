#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
int cpid;
int main() {
	printf("Diese Loesung wurde erstellt von Lukas Scheler \n");
	
	// Neuen Prozess erstellen
	cpid = fork();

	// Ausgabe der Prozess-IDs des Eltern- und Kindprozesses

	printf("Elternprozess: %d Kinderprozess: %d \n", getppid(), getpid());
    
	while(1) {
    }

    return 0;

}
