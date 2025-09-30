#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include <string.h>

int main()
{
   int fd;
   char *myfifo = "/tmp/myfifo";

   mkfifo(myfifo, 0666);

   char arr1[80], arr2[80];
   int bytesWritten, bytesRead;

   while (1)
   {
      fd = open(myfifo, O_WRONLY);
      fgets(arr2, 80, stdin);
      bytesWritten = write(fd, arr2, strlen(arr2) + 1);
      printf("Bytes written: %d\n", bytesWritten);
      close(fd);

      fd = open(myfifo, O_RDONLY);
      bytesRead = read(fd, arr1, sizeof(arr1));
      printf("USER 2: %s", arr1);
      printf("Bytes read: %d\n", bytesRead);
      close(fd);
   }
   return 0;
}
