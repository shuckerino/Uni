#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <sys/wait.h>
#include <time.h>
#include <sys/shm.h>

#define MAX_QUEUE_SIZE 4
#define MAX_COUNSELORS 3

// Shared memory structure
struct shared_data
{
    int waiting_count;
    int counselor_count;
};

// semaphores
int mutex_sem, waiting_sem, counselor_sem, waiting_time_sem;

// shared memory
int shared_memory_id;

void init_semaphores_and_shared_memory()
{
    mutex_sem = semget(IPC_PRIVATE, 1, IPC_CREAT | IPC_EXCL | 0777);
    waiting_sem = semget(IPC_PRIVATE, 1, IPC_CREAT | IPC_EXCL | 0777);
    counselor_sem = semget(IPC_PRIVATE, 1, IPC_CREAT | IPC_EXCL | 0777);
    waiting_time_sem = semget(IPC_PRIVATE, 1, IPC_CREAT | IPC_EXCL | 0777);

    if (mutex_sem < 0 || waiting_sem < 0 || counselor_sem < 0 || waiting_time_sem < 0)
    {
        printf("Error while creating semaphores!\n");
        exit(1);
    }

    // Initialize semaphores
    semctl(mutex_sem, 0, SETVAL, 1);
    semctl(waiting_sem, 0, SETVAL, 1);
    semctl(counselor_sem, 0, SETVAL, 1);
    semctl(waiting_time_sem, 0, SETVAL, 1);

    // Initialize shared memory
    shared_memory_id = shmget(IPC_PRIVATE, sizeof(struct shared_data), IPC_CREAT | IPC_EXCL | 0777);

    if (shared_memory_id < 0)
    {
        printf("Error while creating shared memory!\n");
    }
}

int wait_sem(int semid)
{
    struct sembuf sops;
    sops.sem_num = 0;
    sops.sem_op = -1;
    sops.sem_flg = 0;
    return semop(semid, &sops, 1);
}

int signal_sem(int semid)
{
    struct sembuf sops;
    sops.sem_num = 0;
    sops.sem_op = 1;
    sops.sem_flg = 0;
    return semop(semid, &sops, 1);
}

int get_random_time(int min, int max)
{
    return min + rand() % (max - min + 1);
}

void handle_incoming_calls()
{
    // attach shared memory address space
    struct shared_data *shared_data = (struct shared_data *)shmat(shared_memory_id, NULL, 0);

    // Check for failure
    if (shared_data == NULL)
    {
        printf("Error while attaching shared memory address for incoming call handler!\n");
        exit(1);
    }

    while (1)
    {
        // delay the next call by random number between zero and two
        sleep(get_random_time(0, 2));

        wait_sem(mutex_sem); // for accessing shared_data
        if (shared_data->waiting_count < MAX_QUEUE_SIZE)
        {
            shared_data->waiting_count++;
            signal_sem(mutex_sem); // end of accessing shared data

            wait_sem(waiting_sem);
            wait_sem(waiting_time_sem);

            printf("Call is handled by counselor.\n");

            signal_sem(waiting_time_sem);
            wait_sem(mutex_sem);
            shared_data->waiting_count--;
            signal_sem(mutex_sem);
            signal_sem(counselor_sem);
        }
        else
        {
            signal_sem(mutex_sem);
            printf("The hotline is overloaded. Please try again some time later.\n");
        }
    }

    // detach address space from current process
    if (shmdt(shared_data) == -1)
    {
        printf("Error while detaching shared memory from address space of current process!\n");
        exit(1);
    }
}

void counselor()
{
    // attach shared memory address space
    struct shared_data *shared_data = (struct shared_data *)shmat(shared_memory_id, NULL, 0);

    // Check for failure
    if (shared_data == NULL)
    {
        printf("Error while attaching shared memory address for counselor function!\n");
        exit(1);
    }

    while (1)
    {
        wait_sem(counselor_sem);

        wait_sem(mutex_sem);
        if (shared_data->counselor_count < MAX_COUNSELORS)
        {
            shared_data->counselor_count--;
            signal_sem(mutex_sem);

            printf("Counselor takes next call.\n");

            sleep(get_random_time(0, 5)); // simulate random duration of call between 0 and 5

            wait_sem(mutex_sem);
            shared_data->counselor_count++;
            signal_sem(mutex_sem);
            signal_sem(counselor_sem);
        }
        else
        {
            signal_sem(mutex_sem);
        }
    }

    // detach address space from current process
    if (shmdt(shared_data) == -1)
    {
        printf("Error while detaching shared memory from address space of current process!\n");
        exit(1);
    }
}

int main()
{
    printf("This solution was created by Rinaldo Schuster.\n");

    init_semaphores_and_shared_memory();

    pid_t pid_1 = fork();

    if (pid_1 < -1)
    {
        printf("Error while forking child process.\n");
        exit(1);
    }
    else if (pid_1 == 0)
    { // child process
        handle_incoming_calls();
        exit(0);
    }

    // continue with parent process

    for (int i = 0; i < MAX_COUNSELORS; i++)
    {
        pid_t pid_x = fork();

        if (pid_x < -1)
        {
            printf("Error while forking child process.\n");
            exit(1);
        }
        else if (pid_x == 0)
        {
            counselor();
            exit(0);
        }
    }

    // Wait for all processes to finish
    for (int i = 0; i < MAX_COUNSELORS; i++)
    {
        wait(NULL);
    }

    // delete shared memory
    if (shmctl(shared_memory_id, IPC_RMID, NULL) == -1)
    {
        printf("Error while deleting shared memory!\n");
        exit(1);
    }

    return 0;
}