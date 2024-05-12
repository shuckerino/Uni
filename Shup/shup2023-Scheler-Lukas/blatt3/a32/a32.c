#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/wait.h>
#include <time.h>


int main(int argc, char *argv[]) {
	printf("Diese Loesung wurde erstellt von Lukas Scheler \n");
	int SHMSZ = sizeof(int);
    if (argc < 3) {
        exit(1);
    }
    
    int loop_count = atoi(argv[1]);
    int seed = atoi(argv[2]);
    srand(seed);
    
    int shmid;
    key_t key = IPC_PRIVATE;
    int *shm, *s;
    
    if ((shmid = shmget(key, SHMSZ, IPC_CREAT | 0777)) < 0) { // Erstellung des gemeinsam genutzten Speicherbereichs
        printf("Fehler beim rstellen des Shared Memory \n");
        exit(1);
    }
    
    if ((shm = shmat(shmid, NULL, 0)) == (int *) -1) { // Verbindung des Speicherbereichs zum Adressraum des Prozesses
        printf("Fehler beim Einbinden des Shared Memory \n");
        exit(1);
    }
    
    s = shm;
    
    pid_t pid = fork();
    
    if (pid < 0) {
        printf("Fehler beim Erzeugen des Kindprozesses \n");
        exit(1);
    }
    else if (pid == 0) { // Kindprozess
        for (int i = 0; i < loop_count; i++) {
            printf("Kindprozess liest: %d\n", *s); // Lesen des gemeinsam genutzten Speicherbereichs
        }
        exit(0);
    }
    else { // Elternprozess
        for (int i = 0; i < loop_count; i++) {
            *s = rand(); // Setzen des Wertes des gemeinsam genutzten Speicherbereichs
            printf("Elternprozess schreibt: %d\n", *s);
        }
        wait(NULL); // Warten auf das Ende des Kindprozesses
    }
    
    // Trennung des Speicherbereichs vom Adressraum des Prozesses
    if (shmdt(shm) == -1) {
        printf("Fehler beim trennen des Shared Memory \n");
        exit(1);
    }
    
    // Löschen des gemeinsam genutzten Speicherbereichs
    if (shmctl(shmid, IPC_RMID, NULL) == -1) {
        printf("Fehler beim loeschen des Shared Memory \n");
        exit(1);
    }
    
    return 0;
}
