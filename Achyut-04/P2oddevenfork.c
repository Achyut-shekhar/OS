#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>

int main(){
    printf("\n\t\t\t\t\tNAME: ACHYUT SHEKHAR SINGH | SECTION: C (G1) | ROLL NUMBER: 04\n");
    printf(" P2: Parent Process Computes the SUM OF EVEN and Child\n Process Computes the sum of ODD NUMBERS using fork\n\n");
    printf(" NAME: AYUSH RAMOLA | SECTION: C (G1) | ROLL NUMBER: 17\n\n");
    int n;
    printf(" Enter the size of the array: ");
    scanf("%d", &n);
    int arr[n];
    printf(" Enter the array elements: ");
    for(int i = 0; i < n; i++){
        scanf("%d", &arr[i]);
    }
    printf("\n");
    pid_t child_pid = fork();
    if(child_pid == 0){
        int odsum = 0;
        for(int i = 0; i < n; i++){
            if(arr[i] % 2 != 0) odsum += arr[i];
        }
        printf(" Sum of odd elements calculated in Child: %d\n", odsum);
    }else if(child_pid > 0){
        int esum = 0;
        for(int i = 0; i < n; i++){
            if(arr[i] % 2 == 0) esum += arr[i];
        }
        printf(" Sum of even elements calculated in Parent: %d\n", esum);
    }
    return 0;
}
