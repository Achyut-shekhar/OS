#include <stdio.h>
#include <string.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <unistd.h>

int main()
{
    printf("\n\t\t\t\t\tNAME: ACHYUT SHEKHAR SINGH | SECTION: C (G1) | ROLL NUMBER: 04\n");
    int fd;
    char *myfifo = "/tmp/myfifo";
    mkfifo(myfifo, 0666);

    char str1[80], str2[80];
    int bytesRead, bytesWritten;

    while (1)
    {
        fd = open(myfifo, O_RDONLY);
        bytesRead = read(fd, str1, 80);
        printf("User1: %s", str1);
        printf("Bytes read: %d\n", bytesRead);
        close(fd);

        fd = open(myfifo, O_WRONLY);
        fgets(str2, 80, stdin);
        bytesWritten = write(fd, str2, strlen(str2) + 1);
        printf("Bytes written: %d\n", bytesWritten);
        close(fd);
    }

    return 0;
}
