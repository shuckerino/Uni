#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/sem.h>
#include <sys/types.h>
#include <sys/ipc.h>

union semun {
    int val;
    struct semid_ds *buf;
    short *array;
};

// Erstellt eine Semaphore und initialisiert alle Werte auf 0
int create_semaphore(int nsems) {
    // Semaphor-ID mit nsems Semaphore erstellen
    int semid = semget(IPC_PRIVATE, nsems, IPC_CREAT | IPC_EXCL | 0777);
    if (semid < 0) {
        perror("Fehler beim erstellen der Semaphore");
        exit(1);
    }

    // Initialisiere alle Semaphore-Werte auf 0
    union semun arg;
    arg.val = 0;
    for (int i = 0; i < nsems; i++) {
        if (semctl(semid, i, SETVAL, arg) < 0) {
            perror("Fehler beim setzen eines Wertes der Semaphore");
            exit(1);
        }
    }

    return semid;
}

// Inkrementiert den Semaphore-Wert um 1
void sem_signal(int semid, int semnum) {
    struct sembuf buf = {semnum, 1, SEM_UNDO};
    if (semop(semid, &buf, 1) < 0) {
        perror("Fehler beim Signal einer Semaphore");
        exit(1);
    }
}

// Dekrementiert den Semaphore-Wert um 1
void sem_wait(int semid, int semnum) {
    struct sembuf buf = {semnum, -1, SEM_UNDO};
    if (semop(semid, &buf, 1) < 0) {
        perror("Fehler beim Wait einer Semaphore");
        exit(1);
    }
}

int main() {
	printf("Diese Loesung wurde erstellt von Lukas Scheler \n");
    // Semaphore mit zwei Semaphore-Elementen erstellen
    int semid = create_semaphore(2);

    pid_t pid = fork();
    if (pid < 0) {
        perror("Fehler beim erzeugen eines Kindprozesses");
        exit(1);
    } else if (pid == 0) {
        // Kindprozess
        sem_wait(semid, 0);  // Warten auf Signal des Elternprozesses
        printf("Kindprozess hat das Signal von Semaphore 0 erhalten\n");

        sem_signal(semid, 1);  // Signal an den Elternprozess senden
        exit(0);
    } else {
        // Elternprozess

        sem_signal(semid, 0);  // Signal an den Kindprozess senden
        sem_wait(semid, 1);  // Warten auf Signal des Kindprozesses
        printf("Elternprozess hat das Signal von Semaphore 1 erhalten\n");
    }

    if (semctl(semid, 0, IPC_RMID, NULL) < 0) {
        perror("Fehler beim löschen der Semaphore");
    }

    return 0;
}
