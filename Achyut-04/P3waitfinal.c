#include <stdio.h>
#include <stdlib.h>
#ifdef __unix__
#include <sys/wait.h>
#endif
#include <unistd.h>

int main(){
    printf("\n\t\t\t\t\tNAME: ACHYUT SHEKHAR SINGH | SECTION: C (G1) | ROLL NUMBER: 04\n");
    printf(" P3: Demonstration of WAIT() System Call\n\n");
  
    pid_t child_pid;
    child_pid = fork();
    if(child_pid == 0){
        printf(" I am the child process with PID = %d\n", getpid());
        printf(" My parent is now waiting with parent PID: %d. \n\n", getppid());
        sleep(4);
        exit(0);
    }else if(child_pid > 0){
        printf(" I am the parent process and my PID is %d \n", getpid());
        printf(" and my child is: %d \n", child_pid);
        int waiting_pid = wait(NULL);
        printf(" My child has been terminated with PID %d \n", waiting_pid);
    }
    return 0;
}
