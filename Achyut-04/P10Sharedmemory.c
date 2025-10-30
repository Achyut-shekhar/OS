#include <stdio.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/types.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>

int main()
{
    int shmid;
    char *shared_memory;
    printf("\n\t\t\t\t\tNAME: ACHYUT SHEKHAR SINGH | SECTION: C (G1) | ROLL NUMBER: 04\n");
    key_t Key = ftok("shmfile.txt", 65);
    if (Key == -1)
    {
        perror("ftok");
        exit(1);
    }
    printf("Unique key created using ftok: %d\n", Key);
    shmid = shmget(Key, 1024, 0666 | IPC_CREAT);
    if (shmid == -1)
    {
        perror("shmget");
        exit(1);
    }
    printf("Shared memory id after creation: %d\n", shmid);
    pid_t pid = fork();
    if (pid < 0)
    {
        perror("fork");
        exit(1);
    }
    else if (pid == 0)
    {
        printf("Child (PID: %d) writing data into shared memory...\n", getpid());
        shared_memory = (char *)shmat(shmid, NULL, 0);
        if (shared_memory == (char *)-1)
        {
            perror("shmat");
            exit(1);
        }
        printf("Shared memory attached at address (shmaddr): %p\n", (void *)shared_memory);
        strcpy(shared_memory, "HELLO");
        printf("Data written successfully \n");
    }
    else
    {
        sleep(2);
        printf("Parent (PID: %d) reading from shared memory\n", getpid());
        shared_memory = (char *)shmat(shmid, NULL, 0);
        if (shared_memory == (char *)-1)
        {
            perror("shmat");
            exit(1);
        }
        printf("Shared memory attached at address (shmaddr): %p\n", (void *)shared_memory);
        printf("Received Message = %s \n", shared_memory);
        printf("Size: %lu bytes\n", strlen(shared_memory));
        shmdt(shared_memory);
        printf("Shared memory id after detaching: %d\n", shmid);
        shmctl(shmid, IPC_RMID, NULL);
    }
    return 0;
}
