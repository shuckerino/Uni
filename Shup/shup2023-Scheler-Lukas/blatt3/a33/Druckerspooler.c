#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <sys/shm.h>
#include <semaphore.h>
#include <sys/wait.h>
#include <time.h>
#include <string.h>


typedef struct
{
    int inhalt;
    int seitenanzahl;
} PrintJob;

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

int main(int args, char **argc)
{
    int SHM_SIZE = 5;
    printf("\x1b[32mDruckerspooler gestartet mit Pid %d \x1b[0m\n", getpid());
    int shmid = shmget(atoi(argc[0]), SHM_SIZE * sizeof(PrintJob), IPC_CREAT | 0777);
    PrintJob *array = (PrintJob *)shmat(shmid, NULL, 0);

    int shmidp1 = shmget(atoi(argc[1]), sizeof(PrintJob), IPC_CREAT | 0777);
    PrintJob *shmp1 = (PrintJob *)shmat(shmidp1, NULL, 0);

    int shmidp2 = shmget(atoi(argc[2]), sizeof(PrintJob), IPC_CREAT | 0777);
    PrintJob *shmp2 = (PrintJob *)shmat(shmidp2, NULL, 0);

    if (array == (PrintJob *)-1 || shmp1 == (PrintJob *)-1 || shmp2 == (PrintJob *)-1)
    {
        printf("\x1b[32mFehler beim Befestigen eines Shared Memory \x1b[0m\n");
        exit(1);
    }

    int emptyArray = semget(atoi(argc[3]), 1, IPC_CREAT | 0777);
    int fullArray = semget(atoi(argc[4]), 1, IPC_CREAT | 0777);
    int mutex = semget(atoi(argc[5]), 1, IPC_CREAT | 0777);
    int emptyP1 = semget(atoi(argc[6]), 1, IPC_CREAT | 0777);
    int fullP1 = semget(atoi(argc[7]), 1, IPC_CREAT | 0777);
    int emptyP2 = semget(atoi(argc[8]), 1, IPC_CREAT | 0777);
    int fullP2 = semget(atoi(argc[9]), 1, IPC_CREAT | 0777);

    int lastJob = 0;
    int currentPrinter = 1;
    int counterFull = 0;
    PrintJob newJob;
    while (1)
    {
        // Warte, bis mindestens ein Platz im Shared-Memory Array voll ist
        wait_sem(fullArray);

        // Warte, bis der Zugriff auf das Shared-Memory Array erlaubt ist
        wait_sem(mutex);

        // Entnehme dem Shared-Memory Array einen PrintJob

        newJob.seitenanzahl = 0;
        while (newJob.seitenanzahl == 0)
        {
            newJob.inhalt = array[lastJob].inhalt;
            newJob.seitenanzahl = array[lastJob].seitenanzahl;
            array[lastJob].seitenanzahl = 0;
            if (newJob.seitenanzahl != 0)
            {
                printf("\x1b[32mDruckerspooler hat einen Druckauftrage entnommen mit %d auf %d Seiten \x1b[0m\n", newJob.inhalt, newJob.seitenanzahl);
            }
            if (lastJob == 4)
                lastJob = 0;
            else
                lastJob++;
        }
        for (int i = 0; i < 5; i++)
            if (array[i].seitenanzahl == 0)
                counterFull++;
        printf("\x1b[32mFreie Plaetze: %d \x1b[0m\n", counterFull);
        counterFull = 0;

        // Signalisiere, dass der Zugriff auf das Shared-Memory Array wieder erlaubt ist
        signal_sem(mutex);

        // Signalisiere, dass ein weiterer Platz im Shared-Memory Array frei ist
        signal_sem(emptyArray);

        if (currentPrinter == 1)
        {
            printf("\x1b[32mDruckerspooler hat Drucker %d angefragt mit %d auf %d Seiten \x1b[0m\n", currentPrinter, newJob.inhalt, newJob.seitenanzahl);
            wait_sem(emptyP1);
            shmp1[0] = newJob;
            currentPrinter++;
            signal_sem(fullP1);
        }
        else
        {
            printf("\x1b[32mDruckerspooler hat Drucker %d angefragt mit %d auf %d Seiten \x1b[0m\n", currentPrinter, newJob.inhalt, newJob.seitenanzahl);
            wait_sem(emptyP2);
            shmp2[0] = newJob;
            currentPrinter--;
            signal_sem(fullP2);
        }
    }
    return 0;
}
