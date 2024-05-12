#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/sem.h>
#include <string.h>

int lastJob = 0;

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
    printf("\x1b[34mDrucker gestartet mit Pid %d \x1b[0m\n", getpid());
    int shmidp = shmget(atoi(argc[0]), sizeof(PrintJob), IPC_CREAT | 0777);
    PrintJob *array = (PrintJob *)shmat(shmidp, NULL, 0);

    if (array == (PrintJob *) -1) {
        printf("\x1b[34mFehler beim Befestigen des Shared Memory \x1b[0m\n");
        exit(1);
    }

	int fullPrinter = semget(atoi(argc[1]), 1, IPC_CREAT | 0777);
    int emptyPrinter = semget(atoi(argc[2]), 1, IPC_CREAT | 0777);
    int printerNr = atoi(argc[3]);

    PrintJob newJob;
	while(1) {
        wait_sem(fullPrinter);
		newJob = array[0];
        printf("\x1b[34mDrucker %d druckt gerade %d auf %d Seiten \x1b[0m\n", printerNr, newJob.inhalt, newJob.seitenanzahl);
        sleep(1*newJob.seitenanzahl);
        signal_sem(emptyPrinter);
	}	
}

