#include <stdio.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/types.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>

#define SHM_SIZE 1024  // Define size of shared memory in bytes

int main() {
    printf("Name: Achyut Shekhar Singh\t\tRoll No.: 04\n\n");

    key_t key;
    int shmid;
    char *shmaddr;

    // Step 1: Generate a unique key using ftok
    key = ftok("shmfile", 65);  // ftok creates a key based on a file and id
    if (key == -1) {
        perror("ftok");
        exit(1);
    }
    printf("Unique key created using ftok: %d\n", key);

    // Step 2: Create shared memory segment
    shmid = shmget(key, SHM_SIZE, 0666 | IPC_CREAT);  // Create shared memory with read/write permission
    if (shmid < 0) {
        perror("shmget");
        exit(1);
    }
    printf("Shared memory ID: %d\n", shmid);

    // Step 3: Create a child process
    pid_t pid = fork();
    if (pid < 0) {
        perror("fork");
        exit(1);
    }

    // ===== Child Process - Writer =====
    if (pid == 0) {
        printf("\n[Child] PID: %d - Writing to shared memory...\n", getpid());

        // Step 4: Attach shared memory
        shmaddr = (char *)shmat(shmid, NULL, 0);
        if (shmaddr == (char *)-1) {
            perror("shmat");
            exit(1);
        }
        printf("[Child] Shared memory attached at: %p\n", shmaddr);

        // Step 5: Write message to shared memory
        char msg[] = "Hello from Child to Parent!";
        strcpy(shmaddr, msg);
        printf("[Child] Message written: %s\n", msg);

        // Step 6: Detach from shared memory
        shmdt(shmaddr);
        printf("[Child] Detached from shared memory\n");
    } 
    
    // ===== Parent Process - Reader =====
    else {
        // Wait to ensure child writes first
        sleep(1);

        printf("\n[Parent] PID: %d - Reading from shared memory...\n", getpid());

        // Step 7: Attach to shared memory
        shmaddr = (char *)shmat(shmid, NULL, 0);
        if (shmaddr == (char *)-1) {
            perror("shmat");
            exit(1);
        }
        printf("[Parent] Shared memory attached at: %p\n", shmaddr);

        // Step 8: Read message from shared memory
        printf("[Parent] Message received: %s\n", shmaddr);
        printf("[Parent] Message size: %ld bytes\n", strlen(shmaddr));

        // Step 9: Detach from shared memory
        shmdt(shmaddr);
        printf("[Parent] Detached from shared memory\n");

        // Step 10: Destroy shared memory segment
        if (shmctl(shmid, IPC_RMID, NULL) == -1) {
            perror("shmctl");
            exit(1);
        }
        printf("[Parent] Shared memory segment deleted\n");
    }

    return 0;
}
