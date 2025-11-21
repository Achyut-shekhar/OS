#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/shm.h>
#include <unistd.h>
#include <string.h>
#include <sys/ipc.h>

#define shmsize 1024

int main()
{
  key_t key;
  int shmid;
  char *shmaddr;

  key = ftok("shmfile", 65);
  shmid = shmget(key, shmsize, 0666 | IPC_CREAT);

  printf("Shared memory attached at address (shmaddr): %p\n", (void *)shmaddr);

  pid_t pid = fork();
  if (pid < 0)
  {
    perror("fork");
    exit(1);
  }
  else if (pid == 0)
  {
    printf("Child (PID: %d) writing data into shared memory...\n", getpid());
    shmaddr = (char *)shmat(shmid, NULL, 0);
    strcpy(shmaddr, "hello");
    shmdt(shmaddr);
    printf("Data written successfully \n");
  }
  else
  {
    sleep(1);
    printf("Parent (PID: %d) reading from shared memory\n", getpid());
    shmaddr = (char *)shmat(shmid, NULL, 0);
    printf("Received Message = %s \n", shmaddr);
    printf("Size: %lu bytes\n", strlen(shmaddr));
  }
}