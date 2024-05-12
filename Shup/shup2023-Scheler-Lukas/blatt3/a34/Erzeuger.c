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

char line[1024];

void getMessageFromDatei(FILE *file) {
    if(fgets(line, 1024, file) == NULL) {
        printf("\x1b[32mEnde der Datei erreicht. Programm wird beendet \x1b[0m\n");
        exit(0);
    }
    char *endPos = strchr(line, '\n');
    if(endPos != NULL) {
        *endPos = '\0';
    }
    printf("\x1b[32mNachricht entnommen \x1b[0m\n");
}

void getMessageFromUser() {
    printf("\x1b[32mBitte Nachricht eingeben \x1b[0m\n");
    fgets(line, 1024, stdin);
    char *endPos = strchr(line, '\n');
    if(endPos != NULL) {
        *endPos = '\0';
    }
}

int main(int args, char** argc) {
    printf("\x1b[32mErzeuger mit %d gestartet \x1b[0m\n", getpid());
    int shmidP = shmget(atoi(argc[0]), 7*sizeof(char), IPC_CREAT | 0777);
    int shmidSize = shmget(atoi(argc[1]), 1*sizeof(int), IPC_CREAT | 0777);
    int fullArrayP = semget(atoi(argc[2]), 1, IPC_CREAT | 0777);
    int emptyArrayP = semget(atoi(argc[3]), 1, IPC_CREAT | 0777);
    int fullSizeP = semget(atoi(argc[4]), 1, IPC_CREAT | 0777);
    int emptySizeP = semget(atoi(argc[5]), 1, IPC_CREAT | 0777);
    char* callOption = argc[6];
    char* programName = argc[7];

    char* shm = (char*) shmat(shmidP, NULL, 0);
    int* shmSize = (int*) shmat(shmidSize, NULL, 0);

    int option;
    FILE *file;
    int sizeOfMessage;
    int indexOfSend;

    if(strcmp(callOption, "--interaktiv") == 0) {
            option = 1;
        } else if(strcmp(callOption, "--datei") == 0) {
            option = 2;
            file = fopen(programName, "r");
            if(file == NULL) {
                printf("\x1b[32mFehler beim Oeffnen der Datei \x1b[0m\n");
                return -1;
            }
        } else {
            printf("\x1b[32mFehler bei der Aufrufoption \x1b[0m\n");
            return -1;
    }

    while(1) {
        printf("\x1b[32mNachricht wird erzeugt von %d \x1b[0m\n", getpid());
        if(option == 1)
            getMessageFromUser();
        else getMessageFromDatei(file);

        sizeOfMessage = strlen(line);
        indexOfSend = 0;

        wait_sem(emptySizeP);
        shmSize[0] = sizeOfMessage;
        
        signal_sem(fullSizeP);
        printf("\x1b[32mNachricht wird gesendet von %d \x1b[0m\n", getpid());
        while(indexOfSend < sizeOfMessage) {
            wait_sem(emptyArrayP);
            
            char*  s = shm;
            for(int i = 0; i < 6; i++) {
                if(indexOfSend <= sizeOfMessage) {
                    *s = line[indexOfSend];
                    indexOfSend++;
                    s++;
                }
            }
            *(s) = '\0';
            signal_sem(fullArrayP);
        }
        printf("\x1b[32mNachricht gesendet von %d \x1b[0m\n", getpid());
    }
    return 0;
}
