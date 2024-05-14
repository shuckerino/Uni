#include <stdio.h>
#include <unistd.h>
#include <sys/sem.h>
#include <sys/ipc.h>
#include <stdlib.h>

union semun
{
	int val;
	struct sem_id *buf;
	unsigned short int *array;
};

/// @brief Creates new semaphore set and initializes all values with 0
/// @param num_of_sems_to_create number of semaphores in the semaphore set
/// @return Id of the created semaphore set
int create_semaphore_set(int num_of_sems_to_create)
{
	/*
	IPC_PRIVATE -> create new unique semaphore that is private to its process
	num_of_sems_to_create -> number of sems in the set
	IPC_CREAT -> create if does not exits
	IPC_EXCL -> will fail if key already exists
	0777 -> permissions to read, write and execute
	*/
	int sem_id = semget(IPC_PRIVATE, num_of_sems_to_create, IPC_CREAT | IPC_EXCL | 0777);
	if (sem_id < 0)
	{
		perror("Semaphore konnte nicht erstellt werden.\n");
		exit(1);
	}

	union semun sem;
	sem.val = 0;

	// now set all sems in the set to the specified value (0)
	for (int i = 0; i < num_of_sems_to_create; i++)
	{
		if (semctl(sem_id, i, SETVAL, sem) < 0)
		{
			perror("Ein Semaphorenwert konnte nicht gesetzt werden.\n");
			exit(1);
		}
	}

	return sem_id;
}

void sem_signal(int sem_id, int sem_num)
{
	struct sembuf buf = {sem_num, 1, SEM_UNDO};
	if (semop(sem_id, &buf, 1) < 0)
	{
		perror("Signal für Semaphore konnte nicht ausgeführt werden.\n");
		exit(1);
	}
}

void sem_wait(int sem_id, int sem_num)
{
	struct sembuf buf = {sem_num, -1, SEM_UNDO};
	if (semop(sem_id, &buf, 1) < 0)
	{
		perror("Wait für Semaphore konnte nicht ausgeführt werden.\n");
		exit(1);
	}
}

int main()
{
	printf("Diese Lösung wurde erstellt von Rinaldo Schuster.\n");

	// Create two semaphores
	int semid = create_semaphore_set(2);

	int child_id = fork();

	if (child_id < 0)
	{
		perror("Fehler beim erzeugen eines Kindprozesses");
		exit(1);
	}
	else if (child_id == 0) // child process
	{
		sem_wait(semid, 0); // Warten auf Signal des Elternprozesses
		printf("Kindprozess hat das Signal von Semaphore 0 erhalten\n");

		sem_signal(semid, 1); // Signal an den Elternprozess senden
		exit(0);
	}
	else // parent process
	{
		sem_signal(semid, 0); // Signal an den Kindprozess senden
		sem_wait(semid, 1);	  // Warten auf Signal des Kindprozesses
		printf("Elternprozess hat das Signal von Semaphore 1 erhalten\n");
	}

	if (semctl(semid, 0, IPC_RMID, NULL) < 0)
	{
		perror("Fehler beim löschen der Semaphore");
	}

	return 0;
}
