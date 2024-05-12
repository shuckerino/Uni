#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/sem.h>
#include <string.h>

int wait_sem(int semid)
{
    struct sembuf sops;
    sops.sem_num = 0;
    sops.sem_op = -1;
    sops.sem_flg = 0;
    return semop(semid, &sops, 1);
}

int signal_sem(int semid)
{
    struct sembuf sops;
    sops.sem_num = 0;
    sops.sem_op = 1;
    sops.sem_flg = 0;
    return semop(semid, &sops, 1);
}

int main(int args, char** argc) {
    printf("\x1b[34mEndverbraucher mit %d gestartet \x1b[0m\n", getpid());
    int SHM_SIZE = 7;
    int shmidFinal = shmget(atoi(argc[0]), SHM_SIZE * sizeof(char), IPC_CREAT | 0777);
    int fullFinal = semget(atoi(argc[1]), 1, IPC_CREAT | 0777);
    int emptyFinal = semget(atoi(argc[2]), 1, IPC_CREAT | 0777);

    char* shmFinal = (char*) shmat(shmidFinal, NULL, 0);
    char* line;

    while(1) {
        wait_sem(fullFinal);
        line = shmFinal;
        printf("\x1b[34mEndverbraucher hat folgende Nachricht erhalten: %s \x1b[0m\n", line);
        signal_sem(emptyFinal);
    }
    
    return 0;
}
