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
    printf("\x1b[31mBuffer mit %d gestartet \n", getpid());
    int SHM_SIZE = 7;
    int shmidP = shmget(atoi(argc[0]), SHM_SIZE*sizeof(char), IPC_CREAT | 0777);
    int shmidSize = shmget(atoi(argc[1]), 1*sizeof(char), IPC_CREAT | 0777);
    int shmidFinal = shmget(atoi(argc[2]), 1* sizeof(char), IPC_CREAT | 0777);
    int fullArrayP = semget(atoi(argc[3]), 1, IPC_CREAT | 0777);
    int emptyArrayP = semget(atoi(argc[4]), 1, IPC_CREAT | 0777);
    int fullSizeP = semget(atoi(argc[5]), 1, IPC_CREAT | 0777);
    int emptySizeP = semget(atoi(argc[6]), 1, IPC_CREAT | 0777);
    int fullFinal = semget(atoi(argc[7]), 1, IPC_CREAT | 0777);
    int emptyFinal = semget(atoi(argc[8]), 1, IPC_CREAT | 0777);

    char* shm = (char*) shmat(shmidP, NULL, 0);
    int* shmSize = (int*) shmat(shmidSize, NULL, 0);
    char* shmFinal = (char*) shmat(shmidFinal, NULL, 0);

    int sizeOfMessage;
    int charsRead;
    char line[1024];
    

    while(1) {
        charsRead = 0;

        wait_sem(fullSizeP);
        sizeOfMessage = shmSize[0];
        signal_sem(emptySizeP);

        printf("\x1b[31mNachricht wird empfangen von %d \x1b[0m\n", getpid());
        while(charsRead < sizeOfMessage) {
            wait_sem(fullArrayP);
            char lastRead = '0';
            int i = 0;
            while (lastRead != '\0') {
                lastRead = shm[i];
                i++;
                if (lastRead != '\0') {
                    line[charsRead] = lastRead;
                    charsRead++;
                }
            }
            signal_sem(emptyArrayP);
        }
        printf("\x1b[31mNachricht wurde empfangen von %d \x1b[0m\n", getpid());
        printf("\x1b[31mNachricht wird an Endverbraucher gesendet von %d \x1b[0m\n", getpid());
       
        wait_sem(emptyFinal);
        strcpy(shmFinal, line);
        signal_sem(fullFinal);
    }


    return 0;
}
