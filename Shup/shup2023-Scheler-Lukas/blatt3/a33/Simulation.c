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
#include <time.h>

typedef struct {
    int inhalt;
    int seitenanzahl;
} PrintJob;


int main() { 
	printf("Diese Loesung wurde erstellt von Lukas Scheler \n");
    int SHM_SIZE = 5;
    int shmid, shmidp1, shmidp2;
    PrintJob *shm, *shmp1, *shmp2;
    int mutex, fullP1, emptyP1, fullP2, emptyP2, fullArray, emptyArray;
    int programmCount = 4;
    key_t shmidK, shmidp1K, shmidp2K, mutexK, fullP1K, emptyP1K, fullP2K, emptyP2K, fullArrayK, emptyArrayK;
    shmidK = 1;
    shmidp1K = 2;
    shmidp2K = 3;
    mutexK = 1;
    fullP1K = 2;
    emptyP1K = 3;
    fullP2K = 4;
    emptyP2K = 5;
    fullArrayK = 6;
    emptyArrayK = 7;
    
    time_t start_time, end_time;
    double elapsed_time = 0;
    
    pid_t spooler;
    pid_t printer1;
    pid_t printer2;
    pid_t *programme;
    programme = malloc(sizeof(pid_t)*programmCount);

    PrintJob dummy;
    dummy.inhalt = 0;
    dummy.seitenanzahl = 0;
    

    // Erzeuge den Shared-Memory Bereiche
    shmid = shmget(shmidK, SHM_SIZE * sizeof(PrintJob), IPC_CREAT | 0777);
    shmidp1 = shmget(shmidp1K, 1*sizeof(PrintJob), IPC_CREAT | 0777);
    shmidp2= shmget(shmidp2K, 1*sizeof(PrintJob), IPC_CREAT | 0777);
    if (shmid < 0 || shmidp1 < 0 || shmidp2 < 0) {
        printf("Fehler beim erzeugen eines Shared Memory \n");
        exit(1);
    }
    printf("Shared-Memory erzeugt \n");

    // Befestige den Shared-Memory Bereich im Adressraum des Prozesses
    shm = (PrintJob*) shmat(shmid, NULL, 0);
    shmp1 = (PrintJob*) shmat(shmidp1, NULL, 0);
    shmp2 = (PrintJob*) shmat(shmidp2, NULL, 0);

    if (shm == (PrintJob *) -1 || shmp1 == (PrintJob *) -1 || shmp2 == (PrintJob *) -1) {
        printf("Fehler beim Befestigen eines Shared Memory \n");
        exit(1);
    }

    // Erzeuge die Semaphoren und initialisiere sie mit den richtigen Werten
    mutex = semget(mutexK, 1, IPC_CREAT | 0777);
    fullP1 = semget(fullP1K, 1, IPC_CREAT | 0777);
    emptyP1 = semget(emptyP1K, 1, IPC_CREAT | 0777);
    fullP2 = semget(fullP2K, 1, IPC_CREAT | 0777);
    emptyP2 = semget(emptyP2K, 1, IPC_CREAT | 0777);
    fullArray = semget(fullArrayK, 1, IPC_CREAT | 0777);
    emptyArray = semget(emptyArrayK, 1, IPC_CREAT | 0777);
    

    semctl(mutex, 0, SETVAL, 1); // mutex initialisieren mit Wert 1
    semctl(fullP1, 0, SETVAL, 0); // fullP1 initialisieren mit Wert 0
    semctl(emptyP1, 0, SETVAL, 1); // emptyP1 initialisieren mit Wert 1
    semctl(fullP2, 0, SETVAL, 0); // fullP2 initialisieren mit Wert 0
    semctl(emptyP2, 0, SETVAL, 1); // emptyP2 initialisieren mit Wert 1
    semctl(fullArray, 0, SETVAL, 0); // fullArray initialisieren mit Wert 0 (keine Elemente im Puffer)
    semctl(emptyArray, 0, SETVAL, SHM_SIZE); // emptyArray initialisieren mit Wert SHM_SIZE (Puffer ist leer)
    
    
    // Überprüfe, ob die Semaphoren erfolgreich erstellt und initialisiert wurden
    if (mutex < 0 || fullArray < 0 || emptyArray < 0 || fullP1 < 0 || emptyP1 < 0 || fullP2 < 0 || emptyP2 < 0) {
        printf("Fehler beim Erzeugen einer Semaphore \n");
        exit(1);
    }
    printf("Semaphoren erzeugt \n");
    
    for(int i = 0; i < SHM_SIZE; i++) {
        shm[i] = dummy;
    }
    shmp1[0] = dummy;
    shmp2[0] = dummy;

    spooler = fork();
    if(spooler < 0) {
    	printf("Fehler beim Fork des Druckerspoolers \n");
    	exit(1);
    }
    if(spooler == 0) {
        char arg0[32];
        char arg1[32];
        char arg2[32];
        char arg3[32];
        char arg4[32];
        char arg5[32];
        char arg6[32];
        char arg7[32];
        char arg8[32];
        char arg9[32];
        sprintf(arg0, "%d", shmidK);
        sprintf(arg1, "%d", shmidp1K);
        sprintf(arg2, "%d", shmidp2K);
        sprintf(arg3, "%d", emptyArrayK);
        sprintf(arg4, "%d", fullArrayK);
        sprintf(arg5, "%d", mutexK);
        sprintf(arg6, "%d", emptyP1K);
        sprintf(arg7, "%d", fullP1K);
        sprintf(arg8, "%d", emptyP2K);
        sprintf(arg9, "%d", fullP2K);
        char* array[11] = {arg0, arg1, arg2, arg3, arg4, arg5, arg6, arg7, arg8, arg9, NULL};
        if(execv("Druckerspooler", array) == -1) {
            printf("Fehler beim Erzeugen des Druckerspoolers \n");
            exit(1);
        }
    }
    
    printer1 = fork();
    if(printer1 < 0) {
    	printf("Fehler beim Fork des Drucker 1 \n");
    	exit(1);
    }
    if(printer1 == 0) {
        char arg0[32];
        char arg1[32];
        char arg2[32];
        sprintf(arg0, "%d", shmidp1K);
        sprintf(arg1, "%d", fullP1K);
        sprintf(arg2, "%d", emptyP1K);
        char* array[5] = {arg0, arg1, arg2, "1", NULL};
        if(execv("Drucker", array)== -1) {
            printf("Fehler beim Erzeugen des Drucker 1 \n");
            exit(1);
        }
    }
  
    printer2 = fork();
    if(printer2 < 0) {
    	printf("Fehler beim Fork des Drucker 2 \n");
    	exit(1);
    }
    if(printer2 == 0) {
        char arg0[32];
        char arg1[32];
        char arg2[32];
        sprintf(arg0, "%d", shmidp2K);
        sprintf(arg1, "%d", fullP2K);
        sprintf(arg2, "%d", emptyP2K);
        char* array[5] = {arg0, arg1, arg2, "2", NULL};
        if(execv("Drucker", array)== -1) {
            printf("Fehler beim Erzeugen des Drucker 2 \n");
            exit(1);
        }
    }
	
	// Erzeuge vier Kinderprozesse, diese Erzeugen wieder Kinderprozesse
	time(&start_time);
    for(int i = 0; i < programmCount; i++) {
        programme[i] = fork();
        if(programme[i] < 0) {
        	printf("Fehler beim Fork der Anwendung %d \n", i);
        	exit(1);
        }
        
        if(programme[i] == 0) {
        	while(elapsed_time <= 10) {
        		pid_t childFromChild;
        		childFromChild = fork();
        		if(childFromChild < 0) {
        			printf("Fehler beim Fork der Anwendung %d \n", i);
        			exit(1);
        		}
        		if(childFromChild == 0) {
            		char arg0[32];
            		char arg1[32];
            		char arg2[32];
            		char arg3[32];
           			sprintf(arg0, "%d", shmidK);
            		sprintf(arg1, "%d", emptyArrayK);
            		sprintf(arg2, "%d", fullArrayK);
            		sprintf(arg3, "%d", mutexK);
            		char* array[5] = {arg0, arg1, arg2, arg3, NULL};
            		if(execv("Anwendung", array)== -1) {
                		printf("Fehler beim Erzeugen der Anwendung %d \n", i);
                    		exit(1);
            		}
            	}
            	int status;
            	pid_t finished = wait(&status);
            	printf("Anwendung mit Pid %d beendet \n", finished);
            	int randomSleep = (rand() % 5);
            	time(&end_time);
            	elapsed_time= difftime(end_time, start_time);
            }
            exit(0);
        }
    }

    if (printer1 < 0 || printer2 < 0 || spooler < 0) {
        perror("Fehler beim Forken");
    }
    
    sleep(15);
    

    kill(spooler, 15);
    kill(printer1, 15);
    kill(printer2, 15);
    for(int i = 0; i < programmCount; i++) {
        kill(programme[i], 15);
    }  
    printf("Kinderprozesse beendet \n");


    // Trenne den Shared-Memory Bereich vom Adressraum des Prozesses
    shmdt(shm);
    shmdt(shmp1);
    shmdt(shmp2);
    printf("Speicher wurde abgekoppelt \n");

    // Lösche den Shared-Memory Bereich
    shmctl(shmid, IPC_RMID, NULL);
    shmctl(shmidp1, IPC_RMID, NULL);
    shmctl(shmidp2, IPC_RMID, NULL);
    printf("Speicher wurde gelöscht \n");

    // Lösche die Semaphoren
    semctl(mutex, 0, IPC_RMID);
    semctl(fullP1, 0, IPC_RMID);
    semctl(emptyP1, 0, IPC_RMID);
    semctl(fullP2, 0, IPC_RMID);
    semctl(emptyP2, 0, IPC_RMID);
    semctl(fullArray, 0, IPC_RMID);
    semctl(emptyArray, 0, IPC_RMID);
    printf("Semaphoren wurden gelöscht \n");

    return 0;
}
