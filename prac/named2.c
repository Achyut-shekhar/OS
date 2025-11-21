#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <string.h>
#include <fcntl.h>

int main()
{
  int fd;
  char *myfifo = "/tmp/myfifo";
  mkfifo(myfifo, 0666);
  char arr1[80], arr2[80];
  int bytesWritten, bytesRead;

  while (1)
  {
    fd = open(myfifo, O_RDONLY);
    bytesRead = read(fd, arr2, 80);
    printf("USER 1: %s", arr2);
    printf("Bytes read: %d\n", bytesRead);
    close(fd);

    fd = open(myfifo, O_WRONLY);
    fgets(arr1, 80, stdin);
    bytesWritten = write(fd, arr1, strlen(arr1) + 1);
    printf("Bytes written: %d\n", bytesWritten);
    close(fd);

    
  }
}
