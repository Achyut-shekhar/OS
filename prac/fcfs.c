#include <stdio.h>

typedef struct
{
  int pid; // process id
  int bt;  // burst time
  int at;  // arrival time
  int wt;  // waiting time
  int ct;  // completion time
  int tat; // turn around time
} Process;

int main()
{
  int n, i, j;
  float total_wt = 0, total_tat = 0;

  printf("Input no. of processes: ");
  scanf("%d", &n);

  Process p[n];

  // Input
  for (i = 0; i < n; i++)
  {
    printf("\nEnter PID for process %d: ", i + 1);
    scanf("%d", &p[i].pid);

    printf("Enter Burst Time (BT) for P%d: ", p[i].pid);
    scanf("%d", &p[i].bt);

    printf("Enter Arrival Time (AT) for P%d: ", p[i].pid);
    scanf("%d", &p[i].at);

    p[i].wt = p[i].ct = p[i].tat = 0;
  }

  // Sort by Arrival Time (AT) for FCFS
  for (i = 0; i < n - 1; i++)
  {
    for (j = i + 1; j < n; j++)
    {
      if (p[j].at < p[i].at)
      {
        Process temp = p[i];
        p[i] = p[j];
        p[j] = temp;
      }
    }
  }

  int curr_time = 0;

  // FCFS Scheduling
  for (i = 0; i < n; i++)
  {
    // If CPU is idle, jump time to this process's arrival
    if (curr_time < p[i].at)
      curr_time = p[i].at;

    curr_time += p[i].bt;
    p[i].ct = curr_time;          // Completion Time
    p[i].tat = p[i].ct - p[i].at; // Turnaround Time
    p[i].wt = p[i].tat - p[i].bt; // Waiting Time

    total_tat += p[i].tat;
    total_wt += p[i].wt;
  }

  // Output
  printf("\nPID\tBT\tAT\tCT\tTAT\tWT\n");
  for (i = 0; i < n; i++)
  {
    printf("%d\t%d\t%d\t%d\t%d\t%d\n",
           p[i].pid, p[i].bt, p[i].at,
           p[i].ct, p[i].tat, p[i].wt);
  }

  printf("\nAverage TAT = %.2f\n", total_tat / n);
  printf("Average WT  = %.2f\n", total_wt / n);

  return 0;
}
