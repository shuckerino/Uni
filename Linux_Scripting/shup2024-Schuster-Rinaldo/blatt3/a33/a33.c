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

struct shared_data
{
    int waiting_count;
    int counselor_count;
    int current_customer_id;
};

int mutex_sem, waiting_sem, counselor_sem;
int shared_memory_id;

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

// Initialize semaphores and shared memory
void init_semaphores_and_shared_memory()
{
    mutex_sem = semget(IPC_PRIVATE, 1, IPC_CREAT | 0777);
    waiting_sem = semget(IPC_PRIVATE, 1, IPC_CREAT | 0777);
    counselor_sem = semget(IPC_PRIVATE, 1, IPC_CREAT | 0777);

    if (mutex_sem < 0 || waiting_sem < 0 || counselor_sem < 0)
    {
        perror("Error while creating semaphores!\n");
        exit(1);
    }

    // Initialize semaphores
    semctl(mutex_sem, 0, SETVAL, 1);
    semctl(waiting_sem, 0, SETVAL, 0);
    semctl(counselor_sem, 0, SETVAL, MAX_COUNSELORS);

    // Initialize shared memory
    shared_memory_id = shmget(IPC_PRIVATE, sizeof(struct shared_data), IPC_CREAT | 0777);

    if (shared_memory_id < 0)
    {
        perror("Error while creating shared memory!\n");
        exit(1);
    }

    struct shared_data *shared_data = (struct shared_data *)shmat(shared_memory_id, NULL, 0);
    if (shared_data == (void *)-1)
    {
        perror("Error while attaching shared memory!\n");
        exit(1);
    }

    shared_data->waiting_count = 0;
    shared_data->counselor_count = MAX_COUNSELORS;
    shared_data->current_customer_id = 1;

    if (shmdt(shared_data) == -1)
    {
        perror("Error while detaching shared memory!\n");
        exit(1);
    }
}

int get_random_time(int min, int max)
{
    return min + rand() % (max - min + 1);
}

void handle_incoming_calls()
{
    struct shared_data *shared_data = (struct shared_data *)shmat(shared_memory_id, NULL, 0);
    if (shared_data == (void *)-1)
    {
        perror("Error while attaching shared memory for incoming call handler!\n");
        exit(1);
    }

    while (1)
    {
        sleep(get_random_time(0, 2));

        wait_sem(mutex_sem);
        if (shared_data->waiting_count < MAX_QUEUE_SIZE)
        {
            shared_data->waiting_count++;
            signal_sem(mutex_sem);

            signal_sem(waiting_sem); // Increment to signal, that one more is waiting
            printf("Call is added to the queue. Waiting count: %d\n", shared_data->waiting_count);
        }
        else
        {
            signal_sem(mutex_sem);
            printf("The hotline is overloaded. Please try again later.\n");
        }
    }

    if (shmdt(shared_data) == -1)
    {
        perror("Error while detaching shared memory for incoming call handler!\n");
        exit(1);
    }
}

void counselor()
{
    struct shared_data *shared_data = (struct shared_data *)shmat(shared_memory_id, NULL, 0);
    if (shared_data == (void *)-1)
    {
        perror("Error while attaching shared memory for counselor!\n");
        exit(1);
    }

    int current_customer, current_counselor;

    while (1)
    {
        wait_sem(waiting_sem); // wait for a call in queue
        wait_sem(counselor_sem); // wait for available counselor

        wait_sem(mutex_sem);
        current_customer = shared_data->current_customer_id;
        current_counselor = shared_data->counselor_count;
        printf("Counselor %d takes call from customer Nr. %d.\n", current_counselor, current_customer);
        shared_data->counselor_count--;
        shared_data->waiting_count--;
        shared_data->current_customer_id++;
        signal_sem(mutex_sem);

        sleep(get_random_time(0, 5)); // Simulate random duration of call between 0 and 5
        
        printf("Counselor %d finishes current call with customer %d.\n", current_counselor, current_customer);

        signal_sem(counselor_sem); // Signal that the counselor is available again
        // increment counter of available counselors again
        wait_sem(mutex_sem);
        shared_data->counselor_count++;
        signal_sem(mutex_sem);
    }

    if (shmdt(shared_data) == -1)
    {
        perror("Error while detaching shared memory for counselor!\n");
        exit(1);
    }
}

int main()
{
    printf("This solution was created by Rinaldo Schuster.\n");

    init_semaphores_and_shared_memory();

    pid_t pid = fork();
    if (pid < 0)
    {
        perror("Error while forking child process.\n");
        exit(1);
    }
    else if (pid == 0)
    {
        handle_incoming_calls();
        exit(0);
    }

    // Fork counselor processes
    for (int i = 0; i < MAX_COUNSELORS; i++)
    {
        pid = fork();
        if (pid < 0)
        {
            perror("Error while forking counselor process.\n");
            exit(1);
        }
        else if (pid == 0)
        {
            counselor();
            exit(0);
        }
    }

    // Wait for all child processes to finish
    for (int i = 0; i < MAX_COUNSELORS + 1; i++)
    {
        wait(NULL);
    }

    // Cleanup shared memory and semaphores
    shmctl(shared_memory_id, IPC_RMID, NULL);
    semctl(mutex_sem, 0, IPC_RMID);
    semctl(waiting_sem, 0, IPC_RMID);
    semctl(counselor_sem, 0, IPC_RMID);

    return 0;
}
