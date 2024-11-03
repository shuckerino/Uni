#include <linux/limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>

const int MAX_USER_INPUT = 256;

void display_current_working_directory()
{
	char cwd_buffer[PATH_MAX];
	if (getcwd(cwd_buffer, sizeof(cwd_buffer)) == NULL)
	{
		perror("Could not get current working directory, therefore aborting execution...\n");
		exit(1);
	}
	printf("%s : ", cwd_buffer);
}

int main()
{
	printf("This solution was created by Rinaldo Schuster\n");
	display_current_working_directory();

	char user_input[MAX_USER_INPUT];

	while (fgets(user_input, MAX_USER_INPUT, stdin) != NULL)
	{
		// format user input (remove trailing new line)
		user_input[strcspn(user_input, "\n")] = '\0';

		// check if user wants to cancel with "schluss"
		if (strcmp(user_input, "schluss") == 0)
		{
			printf("Midi Shell was aborted!\n");
			exit(EXIT_SUCCESS);
		}

		// tokenize user input (into command, options, arguments etc.)
		char *args[64];
		int argc = 0;
		args[argc] = strtok(user_input, " ");
		while (args[argc] && argc < 63)
		{
			argc++;
			args[argc] = strtok(NULL, " ");
		}

		// if no command entered
		if (argc == 0)
			continue;

		// check for "cd" command
		if (strcmp(args[0], "cd") == 0)
		{
			if (argc < 2)
			{
				perror("Error: Missing path after \"cd\".\n");
			}
			else
			{
				if (chdir(args[1]) != 0)
				{
					perror("Error while changing directory.\n");
				}
			}
			display_current_working_directory();
			continue;
		}

		// allocate memory for the full_path
		char *full_path = malloc(128 * sizeof(char));

		// bool indicating, if an executable program was found
		int command_found = 0;

		// if no explicit path, we need to fetch the path variable and look for program in these paths
		if (user_input[0] != '/' && user_input[0] != '.')
		{
			// get entire path variable
			char *path_var = getenv("PATH");
			if (path_var == NULL)
			{
				perror("The path variable could not be fetched, aborting program...\n");
				exit(EXIT_FAILURE);
			}

			char path_copy[1024];
			strncpy(path_copy, path_var, sizeof(path_copy));

			// split path variable into paths
			char *path_part = strtok(path_copy, ":");
			while (path_part != NULL)
			{
				sprintf(full_path, "%s/%s", path_part, user_input);

				//  check if path exists
				if (access(full_path, X_OK) == 0)
				{
					command_found = 1;
					break;
				}
				path_part = strtok(NULL, ":"); // continue to get the next token
			}
		}

		if (command_found == 1)
		{
			int child_pid = fork();

			if (child_pid < 0)
			{
				perror("Child process could not be forked, aborting program...\n");
				exit(EXIT_FAILURE);
			}
			else if (child_pid == 0) // code for child process
			{
				printf("The final path to be executed is: %s", full_path);
				execv(full_path, args);

				perror("Error when executing child program...\n");
			}
			else // code for parent process
			{
				int status;
				wait(&status);
				display_current_working_directory();
			}
		}
		else
		{
			printf("Command was not found!\n");
			display_current_working_directory();
		}
	}
	return 0;
}
