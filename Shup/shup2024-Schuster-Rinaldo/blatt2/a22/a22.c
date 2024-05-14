#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <sys/wait.h>

int main(int argc, char *argv[])
{
    printf("This solution was created by Rinaldo Schuster\n");

    if (argc != 5)
    {
        printf("Please make sure to pass 4 arguments that should be outputted...\n");
        exit(EXIT_FAILURE);
    }

    printf("I am the father process with PID %d\n", getpid());
    printf("The first argument is %s\n", argv[1]);

    int child_pid_1 = fork();

    if (child_pid_1 < 0)
    {
        perror("Creation of child process 1 was unsuccessful, aborting execution...\n");
        exit(EXIT_FAILURE);
    }
    else if (child_pid_1 == 0) // code for first child process
    { 

        printf("I am the 1. child process with PID %d\n", getpid());
        printf("The second argument is %s\n", argv[2]);

        while (1)
        {
            sleep(1);
        }
    }
    else // code for parent process
    {
        int child_pid_2 = fork();

        if (child_pid_2 < 0)
        {
            perror("Creation of child process 2 was unsuccessful, aborting execution\n");
            exit(EXIT_FAILURE);
        }
        else if (child_pid_2 == 0) // code for second child process
        { 
            printf("I am the 2. child process with PID %d\n", getpid());
            printf("The third argument is %s\n", argv[3]);
            while (1)
            {
                sleep(1);
            }
        }
        else
        {
            int child_pid_3 = fork();

            if (child_pid_3 < 0)
            {
                perror("Creation of child process 3 was unsuccessful, aborting execution\n");
                exit(EXIT_FAILURE);
            }
            else if (child_pid_3 == 0) // code for third child process
            { 
                printf("I am the 3. child process with PID %d\n", getpid());
                printf("The fourth argument is %s\n", argv[4]);
                sleep(1);
                exit(2);
            }
            else // final code for father process
            { 
                // wait for 2 seconds
                sleep(2);

                // send different signals to each child process
                kill(child_pid_1, SIGTERM);
                kill(child_pid_2, SIGKILL);
                kill(child_pid_3, SIGKILL);

                int exit_status;

                // get exit status of all child processes
                wait(&exit_status);
                printf("Exit status of one of the children: %d\n", exit_status);
                wait(&exit_status);
                printf("Exit status of one of the children: %d\n", exit_status);
                wait(&exit_status);
                printf("Exit status of one of the children: %d\n", exit_status);

                return EXIT_SUCCESS;
            }
        }
    }

    return EXIT_SUCCESS;
}
