#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>

int main()
{
    printf("\n\t\t\t\t\tNAME: ACHYUT SHEKHAR SINGH | SECTION: C (G1) | ROLL NUMBER: 04\n");
    printf(" P4: Demonstration of Zombie and Orphan Processes\n");
    printf(" NAME: AYUSH RAMOLA | SECTION: C (G1) | ROLL NUMBER: 17\n\n");
    pid_t zombie_pid = fork();
    if (zombie_pid > 0)
    {
        printf(" [Parent for Zombie] PID: %d, Child PID: %d\n", getpid(), zombie_pid);
        sleep(10);
        printf(" [Parent for Zombie] My zombie child has now exited.\n\n");
    }
    else if (zombie_pid == 0)
    {
        printf(" [Zombie Child] PID: %d, Parent PID: %d. exiting now.\n", getpid(), getppid());
        exit(0);
    }
    pid_t orphan_pid = fork();
    if (orphan_pid > 0)
    {
        printf(" [Parent for Orphan] PID: %d. My Child is PID: %d exiting now.\n\n", getpid(), orphan_pid);
        exit(0);
    }
    else if (orphan_pid == 0)
    {
        printf(" [Orphan Child] PID: %d, Sleeping 6 seconds...\n", getpid());
        sleep(6);
        printf(" [Orphan Child] After waking, my new parent is: %d\n", getppid());
    }
    return 0;
}
