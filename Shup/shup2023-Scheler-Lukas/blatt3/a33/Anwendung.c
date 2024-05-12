#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/sem.h>
#include <string.h>
#include <time.h>

typedef struct {
    int inhalt;
    int seitenanzahl;
} PrintJob;

int wait_sem(int semid) {
    struct sembuf sops;
    sops.sem_num = 0;
    sops.sem_op = -1;
    sops.sem_flg = 0;
    return semop(semid, &sops, 1);
}

int signal_sem(int semid) {
    struct sembuf sops;
    sops.sem_num = 0;
    sops.sem_op = 1;
    sops.sem_flg = 0;
    return semop(semid, &sops, 1);
}

int main(int args, char** argc) {
    printf("\x1b[31mAnwendung gestartet mit Pid %d \x1b[0m\n", getpid());
    int SHM_SIZE = 5;
	int shmid = shmget(atoi(argc[0]), SHM_SIZE * sizeof(PrintJob), IPC_CREAT | 0777);
    PrintJob *array = (PrintJob *)shmat(shmid, NULL, 0);
    if (array == (PrintJob *) -1) {
        printf("\x1b[31mFehler beim Befestigen des Shared Memory \x1b[0m\n");
        exit(1);
    }
	int emptyArray = semget(atoi(argc[1]), 1, IPC_CREAT | 0777);
	int fullArray = semget(atoi(argc[2]), 1, IPC_CREAT | 0777);
	int mutex = semget(atoi(argc[3]), 1, IPC_CREAT | 0777);

	int seconds;
    PrintJob newJob;
    
	// Warte, bis mindestens ein Platz im Shared-Memory Array frei ist
    wait_sem(emptyArray);

    // Warte, bis der Zugriff auf das Shared-Memory Array erlaubt ist
    wait_sem(mutex);

    // Füge den neuen PrintJob zum Shared-Memory Array hinzu
    srand(time(NULL) + getpid());
    newJob.inhalt = rand();
    newJob.seitenanzahl = (rand() % 5) + 2;
    
    for (int i = 0; i < 5; i++) {
        if (array[i].seitenanzahl == 0) {
            array[i].inhalt = newJob.inhalt;
            array[i].seitenanzahl = newJob.seitenanzahl;
            printf("\x1b[31mAnwendung %d hat einen Auftrag hinzugefuegt mit %d auf %d Seiten \x1b[0m\n", getpid(), newJob.inhalt, newJob.seitenanzahl);       
            break;
        }
    }

    // Signalisiere, dass der Zugriff auf das Shared-Memory Array wieder erlaubt ist
    signal_sem(mutex);

    // Signalisiere, dass ein weiterer Platz im Shared-Memory Array belegt ist
    signal_sem(fullArray);

    
    return 0;
	
}
