#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <sys/shm.h>
#include <semaphore.h>
#include <sys/wait.h>
#include <string.h>

int main() {
	printf("Diese Lösung wurde erstellt von Lukas Scheler \n");
    int SHM_SIZE = 7;
    int shmidFinal, shmidP1, shmidP2, shmidSize1, shmidSize2;
    int fullSizeP1, fullSizeP2, emptySizeP1, emptySizeP2, fullArrayP1, fullArrayP2, emptyArrayP1, emptyArrayP2, fullFinal, emptyFinal;
    key_t shmidFinalK, shmidP1K, shmidP2K, shmidSize1K, shmidSize2K, fullSizeP1K, fullSizeP2K, emptySizeP1K, emptySizeP2K, fullArrayP1K, fullArrayP2K, emptyArrayP1K, emptyArrayP2K, fullFinalK, emptyFinalK;
    shmidFinalK = 1;
    shmidP1K = 2;
    shmidP2K = 3;
    shmidSize1K = 4;
    shmidSize2K = 5;

    fullSizeP1K = 1;
    fullSizeP2K = 2;
    emptySizeP1K = 3;
    emptySizeP2K = 4;
    fullArrayP1K = 5;
    fullArrayP2K = 6;
    emptyArrayP1K = 7;
    emptyArrayP2K = 8;
    fullFinalK = 9;
    emptyFinalK = 10; 

    // Erzeuge den Shared-Memory Bereich mit der Größe SHM_SIZE und dem Key key
    shmidFinal = shmget(shmidFinalK, SHM_SIZE * 1024*sizeof(char), IPC_CREAT | 0777);
    shmidP1 = shmget(shmidP1K, SHM_SIZE*sizeof(char), IPC_CREAT | 0777);
    shmidP2= shmget(shmidP2K, SHM_SIZE*sizeof(char), IPC_CREAT | 0777);
    shmidSize1= shmget(shmidSize1K, 1*sizeof(int), IPC_CREAT | 0777);
    shmidSize2= shmget(shmidSize2K, 1*sizeof(int), IPC_CREAT | 0777);

    if (shmidFinal < 0 || shmidP1 < 0 || shmidP2 < 0 || shmidSize1 < 0 || shmidSize2 < 0) {
        printf("Fehler beim erzeugen eines Shared Memory \n");
        exit(1);
    }
    printf("Shared-Memory erzeugt \n");

    // Erzeuge die Semaphoren und initialisiere sie mit den richtigen Werten
    fullSizeP1 = semget(fullSizeP1K, 1, IPC_CREAT | 0777);
    emptySizeP1 = semget(emptySizeP1K, 1, IPC_CREAT | 0777);
    fullSizeP2 = semget(fullSizeP2K, 1, IPC_CREAT | 0777);
    emptySizeP2 = semget(emptySizeP2K, 1, IPC_CREAT | 0777);
    fullArrayP1 = semget(fullArrayP1K, 1, IPC_CREAT | 0777);
    emptyArrayP1 = semget(emptyArrayP1K, 1, IPC_CREAT | 0777);
    fullArrayP2 = semget(fullArrayP2K, 1, IPC_CREAT | 0777);
    emptyArrayP2 = semget(emptyArrayP2K, 1, IPC_CREAT | 0777);
    fullFinal = semget(fullFinalK, 1, IPC_CREAT | 0777);
    emptyFinal = semget(emptyFinalK, 1, IPC_CREAT | 0777);
    

    semctl(fullSizeP1, 0, SETVAL, 0);
    semctl(emptySizeP1, 0, SETVAL, 1); 
    semctl(fullSizeP2, 0, SETVAL, 0);
    semctl(emptySizeP2, 0, SETVAL, 1); 
    semctl(fullArrayP1, 0, SETVAL, 0); 
    semctl(emptyArrayP1, 0, SETVAL, 1); 
    semctl(fullArrayP2, 0, SETVAL, 0); 
    semctl(emptyArrayP2, 0, SETVAL, 1); 
    semctl(fullFinal, 0, SETVAL, 0);
    semctl(emptyFinal, 0, SETVAL, 1); 

    // Überprüfe, ob die Semaphoren erfolgreich erstellt und initialisiert wurden
    if (fullSizeP1 < 0 || emptySizeP1 < 0 || fullArrayP1 < 0 || emptyArrayP1 < 0 || fullSizeP2 < 0 || emptySizeP2 < 0 || fullArrayP2 < 0 || emptyArrayP2 < 0 || fullFinal < 0 || emptyFinal < 0) {
        printf("Fehler beim Erzeugen einer Semaphore \n");
        exit(1);
    }
    printf("Semaphoren erzeugt \n");

    pid_t programm1;
    pid_t programm2;
    pid_t buffer1;
    pid_t buffer2;
    pid_t endUser;
    
    /*
    programm1 = fork();
    if(programm1 == 0) {
        char arg0[32];
        char arg1[32];
        char arg2[32];
        char arg3[32];
        char arg4[32];
        char arg5[32];
        char arg6[32] = "--interaktiv";
        sprintf(arg0, "%d", shmidP1K);
        sprintf(arg1, "%d", shmidSize1K);
        sprintf(arg2, "%d", fullArrayP1K);
        sprintf(arg3, "%d", emptyArrayP1K);
        sprintf(arg4, "%d", fullSizeP1K);
        sprintf(arg5, "%d", emptySizeP1K);
        char* array[8] = {arg0, arg1, arg2, arg3, arg4, arg5, arg6, NULL};
        if(execv("Erzeuger", array)== -1) {
            perror("Erzeuger 1");
            exit(1);
        }
    }
    */

    programm1 = fork();
    if(programm1 == 0) {
        char arg0[32];
        char arg1[32];
        char arg2[32];
        char arg3[32];
        char arg4[32];
        char arg5[32];
        char arg6[32] = "--datei";
        char arg7[32] = "Input1";
        sprintf(arg0, "%d", shmidP1K);
        sprintf(arg1, "%d", shmidSize1K);
        sprintf(arg2, "%d", fullArrayP1K);
        sprintf(arg3, "%d", emptyArrayP1K);
        sprintf(arg4, "%d", fullSizeP1K);
        sprintf(arg5, "%d", emptySizeP1K);
        char* array[9] = {arg0, arg1, arg2, arg3, arg4, arg5, arg6, arg7, NULL};
        if(execv("Erzeuger", array)== -1) {
            printf("Fehler beim Erzeugen des Erzeugers 1 \n");
            exit(1);
        }
    }
    programm2 = fork();
    if(programm2 == 0) {
        char arg0[32];
        char arg1[32];
        char arg2[32];
        char arg3[32];
        char arg4[32];
        char arg5[32];
        char arg6[32] = "--datei";
        char arg7[32] = "Input2";
        sprintf(arg0, "%d", shmidP2K);
        sprintf(arg1, "%d", shmidSize2K);
        sprintf(arg2, "%d", fullArrayP2K);
        sprintf(arg3, "%d", emptyArrayP2K);
        sprintf(arg4, "%d", fullSizeP2K);
        sprintf(arg5, "%d", emptySizeP2K);
        char* array[9] = {arg0, arg1, arg2, arg3, arg4, arg5, arg6, arg7, NULL};
        if(execv("Erzeuger", array)== -1) {
            printf("Fehler beim Erzeugen des Erzeugers 2 \n");
            exit(1);
        }
    }

    buffer1 = fork();
    if(buffer1 == 0) {
        char arg0[32];
        char arg1[32];
        char arg2[32];
        char arg3[32];
        char arg4[32];
        char arg5[32];
        char arg6[32];
        char arg7[32];
        char arg8[32];
        sprintf(arg0, "%d", shmidP1K);
        sprintf(arg1, "%d", shmidSize1K);
        sprintf(arg2, "%d", shmidFinalK);
        sprintf(arg3, "%d", fullArrayP1K);
        sprintf(arg4, "%d", emptyArrayP1K);
        sprintf(arg5, "%d", fullSizeP1K);
        sprintf(arg6, "%d", emptySizeP1K);
        sprintf(arg7, "%d", fullFinalK);
        sprintf(arg8, "%d", emptyFinalK);
        char* array[10] = {arg0, arg1, arg2, arg3, arg4, arg5, arg6, arg7, arg8, NULL};
        if(execv("Buffer", array)== -1) {
            printf("Fehler beim Erzeugen des Buffer 1 \n");
            exit(1);
        }
    }

    buffer2 = fork();
    if(buffer2 == 0) {
        char arg0[32];
        char arg1[32];
        char arg2[32];
        char arg3[32];
        char arg4[32];
        char arg5[32];
        char arg6[32];
        char arg7[32];
        char arg8[32];
        sprintf(arg0, "%d", shmidP2K);
        sprintf(arg1, "%d", shmidSize2K);
        sprintf(arg2, "%d", shmidFinalK);
        sprintf(arg3, "%d", fullArrayP2K);
        sprintf(arg4, "%d", emptyArrayP2K);
        sprintf(arg5, "%d", fullSizeP2K);
        sprintf(arg6, "%d", emptySizeP2K);
        sprintf(arg7, "%d", fullFinalK);
        sprintf(arg8, "%d", emptyFinalK);
        char* array[10] = {arg0, arg1, arg2, arg3, arg4, arg5, arg6, arg7, arg8, NULL};
        if(execv("Buffer", array)== -1) {
            printf("Fehler beim Erzeugen des Buffer 2 \n");
            exit(1);
        }
    }

    endUser = fork();
    if(endUser == 0) {
        char arg0[32];
        char arg1[32];
        char arg2[32];
        sprintf(arg0, "%d", shmidFinalK);
        sprintf(arg1, "%d", fullFinalK);
        sprintf(arg2, "%d", emptyFinalK);
        char* array[4] = {arg0, arg1, arg2, NULL};
        if(execv("Endverbraucher", array)== -1) {
            printf("Fehler beim Erzeugen des Endverbraucher \n");
            exit(1);
        }
    }

    sleep(10);


    kill(programm1, 15);
    kill(programm2, 15);
    kill(buffer1, 15);
    kill(buffer2, 15);
    kill(endUser, 15);

	// Lösche den Shared-Memory Bereich
    shmctl(shmidFinal, IPC_RMID, NULL);
    shmctl(shmidP1, IPC_RMID, NULL);
    shmctl(shmidP2, IPC_RMID, NULL);
    shmctl(shmidSize1, IPC_RMID, NULL);
    shmctl(shmidSize2, IPC_RMID, NULL);
    printf("Speicher wurde gelöscht \n");

    // Lösche die Semaphoren
    semctl(fullSizeP1, 0, IPC_RMID);
    semctl(emptySizeP1, 0, IPC_RMID);
    semctl(fullArrayP1, 0, IPC_RMID);
    semctl(emptyArrayP1, 0, IPC_RMID);
    semctl(fullSizeP2, 0, IPC_RMID);
    semctl(emptySizeP2, 0, IPC_RMID);
    semctl(fullArrayP2, 0, IPC_RMID);
    semctl(emptyArrayP2, 0, IPC_RMID);
    semctl(fullFinal, 0, IPC_RMID);
    semctl(emptyFinal, 0, IPC_RMID);
    printf("Semaphoren wurden gelöscht \n");
    
}
