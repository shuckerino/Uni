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
        printf("The given command line arguments were not valid. Please make sure to pass 4 arguments that should be outputted...\n");
        return EXIT_FAILURE;
    }

    // output PID and first CL-Argument
    printf("I am the father process with PID %d\n", getpid());
    printf("The first argument is %s\n", argv[1]);

    int child_pid_1 = fork();

    if (child_pid_1 < 0)
    {
        printf("Creation of child process 1 was unsuccessful, aborting execution...\n");
        return EXIT_FAILURE;
    }
    else if (child_pid_1 == 0)
    { // code for first child process
        
        printf("I am the 1. child process with PID %d\n", getpid());
        printf("The second argument is %s\n", argv[2]);

        while (1)
        {
            sleep(1);
        }
    }
    else
    {
        int child_pid_2 = fork();

        if (child_pid_2 < 0)
        {
            printf("Creation of child process 2 was unsuccessful, aborting execution\n");
            return EXIT_FAILURE;
        }
        else if (child_pid_2 == 0)
        { // code for second child process
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
                printf("Creation of child process 3 was unsuccessful, aborting execution\n");
                return EXIT_FAILURE;
            }
            else if (child_pid_3 == 0)
            { // code for third child process
                printf("I am the 3. child process with PID %d\n", getpid());
                printf("The fourth argument is %s\n", argv[4]);
                sleep(1);
                exit(2);
            }
            else
            { // final code for father process
                sleep(2);

                // send different signals to each child process
                kill(child_pid_1, SIGTERM);
                kill(child_pid_2, SIGKILL);
                kill(child_pid_3, SIGKILL);
               
                int exit_status;
                
                // get exit status of all child processes
                wait(&exit_status);
                printf("Normal exit status of one of the children: %d\n", exit_status);
                printf("Translated exit status of one of the children: %d\n", WEXITSTATUS(exit_status));
                wait(&exit_status);
                printf("Normal exit status of one of the children: %d\n", exit_status);
                printf("Translated exit status of one of the children: %d\n", WEXITSTATUS(exit_status));
                wait(&exit_status);
                printf("Normal exit status of one of the children: %d\n", exit_status);
                printf("Translated exit status of one of the children: %d\n", WEXITSTATUS(exit_status));

                return EXIT_SUCCESS;
            }
        }
    }

    return EXIT_SUCCESS;
}
