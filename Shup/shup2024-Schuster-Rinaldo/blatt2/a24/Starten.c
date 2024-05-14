#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <errno.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
	printf("This solution was created by Rinaldo Schuster\n");

	if (argc < 2)
	{
		printf("Please pass some arguments to pass to the new process.\n");
		exit(EXIT_FAILURE);
	}

	int child_pid = fork();

	if (child_pid < 0)
	{
		perror("Error forking child process.\n");
		exit(EXIT_FAILURE);
	}
	else if (child_pid == 0) // code for child process
	{
		execv(argv[1], argv);

		// check for errors
		printf("Error number is %d\n", errno);
		perror("Error");
		printf("Execution of program failed.\n");
	}
	else // code for parent process
	{
		int status;
		wait(&status);

		printf("Exit status of child process with PID %d is %d\n", child_pid, WEXITSTATUS(status));
	}

	return 0;
}
