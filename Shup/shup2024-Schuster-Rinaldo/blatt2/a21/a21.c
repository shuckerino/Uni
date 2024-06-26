#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main()
{
	printf("This solution was created by Rinaldo Schuster\n");

	// create new child process
	int p_id = fork();

	// check if fork failed
	if (p_id < 0)
	{
		perror("Creating child process failed, aborting execution...\n");
		exit(EXIT_FAILURE);
	}
	else if (p_id == 0) // code for child process
	{ 
		while (1)
		{
			printf("I am the child process with PID = %d and PPID = %d\n", getpid(), getppid());
			sleep(1);
		}
	}
	else // code for parent process
	{ 
		while (1)
		{
			printf("I am the father process with PID = %d and PPID = %d\n", getpid(), getppid());
			sleep(1);
		}
	}

	return EXIT_SUCCESS;
}
