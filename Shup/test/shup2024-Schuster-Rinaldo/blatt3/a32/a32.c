#include <stdio.h>
#include <stdlib.h>
#include <sys/sem.h>
#include <sys/types.h>
#include <sys/shm.h>
#include <unistd.h>
#include <sys/wait.h>

int main(int argc, char *argv[])
{
    printf("This solution was created by Rinaldo Schuster\n");

    if (argc != 3)
    {
        printf("Please specify the number of iterations and the seed for the random generator!\n");
        exit(EXIT_FAILURE);
    }

    int loop_count = atoi(argv[1]);
    int seed = atoi(argv[2]);
    srand(seed);

    int shared_memory_id;
    key_t shared_memory_key = IPC_PRIVATE;
    int *shared_memory_address;

    // create shared memory
    shared_memory_id = shmget(shared_memory_key, sizeof(int), IPC_CREAT | IPC_EXCL | 0777);

    // check for failure
    if (shared_memory_id < 0)
    {
        printf("Error while creating shared memory!\n");
        exit(EXIT_FAILURE);
    }

    // attach shared memory segment to address space of current process
    shared_memory_address = shmat(shared_memory_id, NULL, 0);

    // check for failure
    if (shared_memory_address == (int *)-1)
    {
        printf("Error while attaching shared memory to address space of current process!\n");
        exit(EXIT_FAILURE);
    }

    pid_t process_id = fork();

    if (process_id < 0)
    {
        printf("Error while forking child process!\n");
        exit(1);
    }
    else if (process_id == 0) // Child process
    {
        // reading from shared memory
        for (int i = 0; i < loop_count; i++)
        {
            printf("Child proceses reading from shared memory: %d\n", *shared_memory_address);
        }
        exit(0);
    }
    else // Parent process
    {
        // writing to shared memory
        for (int i = 0; i < loop_count; i++)
        {
            *shared_memory_address = rand();
            printf("Parent process writing into shared memory: %d\n", *shared_memory_address);
        }

        // wait for child process to terminate
        wait(NULL);
    }

    clean_shared_memory(shared_memory_id, shared_memory_address);

    return 0;
}

void clean_shared_memory(int shared_memory_id, int *shared_memory_address)
{
    if (shmdt(shared_memory_address) == -1)
    {
        perror("Error while detaching shared memory from address space of current process!\n");
    }

    if (shmctl(shared_memory_id, IPC_RMID, NULL) == -1)
    {
        perror("Error while deleting shared memory!\n");
    }
}