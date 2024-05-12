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

int handle_incoming_calls()
{
    // attach shared memory address space
    struct shared_data *shared_data = (struct shared_data *)shmat(shared_memory_id, NULL, 0);

    // TODO: check right with cast
    if (shared_data == -1)
    {
        printf("Error while attaching shared memory address for incoming call handler!\n");
        exit(1);
    }

    while (1)
    {
        // delay the next call by random number between zero and two
        sleep(get_random_time(0, 2));

        wait_sem(mutex_sem);
        if (shared_data->waiting_count < MAX_QUEUE_SIZE)
        {
            shared_data->waiting_count++;
            
        }
        else
        {
            signal_sem(mutex_sem);
            printf("The hotline is overloaded. Please try again some time later.\n");
        }
    }
}

int main()
{
    init_semaphores_and_shared_memory();
}