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

int create_semaphore_set(int num_of_sems_to_create)
{
	int sem_id = semget(IPC_PRIVATE, num_of_sems_to_create, IPC_CREAT | IPC_EXCL | 0777);
	if (sem_id < 0)
	{
		perror("Semaphore could not be created.\n");
		exit(1);
	}

	union semun sem;
	sem.val = 0;

	// now set all sems in the set to the specified value (0)
	for (int i = 0; i < num_of_sems_to_create; i++)
	{
		if (semctl(sem_id, i, SETVAL, sem) < 0)
		{
			perror("Error while setting the semaphore values.\n");

			// delete semaphore
			if (semctl(sem_id, 0, IPC_RMID, NULL) < 0)
			{
				perror("Error while deleting semaphore during cleanup.\n");
			}
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
		perror("Signal could not be executed for semaphore.\n");
		exit(1);
	}
}

void sem_wait(int sem_id, int sem_num)
{
	struct sembuf buf = {sem_num, -1, SEM_UNDO};
	if (semop(sem_id, &buf, 1) < 0)
	{
		perror("Wait could not be executed for semaphore.\n");
		exit(1);
	}
}

int main()
{
	printf("This solution was created by Rinaldo Schuster\n");

	// Create two semaphores
	int semid = create_semaphore_set(2);

	int child_id = fork();

	if (child_id < 0)
	{
		perror("Error while creating child process.\n");
		if (semctl(semid, 0, IPC_RMID, NULL) < 0)
		{
			perror("Error while deleting semaphore during cleanup");
		}
		exit(1);
	}
	else if (child_id == 0) // child process
	{
		sem_wait(semid, 0); // Warten auf Signal des Elternprozesses
		printf("Child process received signal from Semaphore 0.\n");

		sem_signal(semid, 1); // signal to parent process
		exit(0);
	}
	else // parent process
	{
		sem_signal(semid, 0); // Signal to child process
		sem_wait(semid, 1);	  // wait for signal of child process
		printf("Parent process received signal from Semaphore 1.\n");

		// wait for child process to finish
		if (wait(NULL) < 0)
		{
			perror("Error while waiting for child process.\n");
		}
	}

	if (semctl(semid, 0, IPC_RMID, NULL) < 0)
	{
		perror("Error while deleting semaphore.\n");
	}

	return 0;
}
