#include <stdio.h>

typedef struct
{
  int pid, at, bt, wt, tat, ct;
} Process;

int main()
{
  int n;
  printf("Input number of processes: ");
  scanf("%d", &n);

  Process p[n];
  float total_wt = 0, total_tat = 0;

  printf("Input arrival times:\n");
  for (int i = 0; i < n; i++)
  {
    p[i].pid = i + 1;
    printf("Process %d: ", i + 1);
    scanf("%d", &p[i].at);
  }

  printf("Input burst times:\n");
  for (int i = 0; i < n; i++)
  {
    printf("Process %d: ", i + 1);
    scanf("%d", &p[i].bt);
  }
//sorting according to the arrival time
  for (int i = 0; i < n - 1; i++)
  {
    for (int j = i + 1; j < n; j++)
    {
      if (p[i].at > p[j].at)
      {
        Process temp = p[i];
        p[i] = p[j];
        p[j] = temp;
      }
    }
  }
//calculating waiting time turnaround time and completion time
  int time = 0;
  for (int i = 0; i < n; i++)
  {
    if (time < p[i].at) 
      time = p[i].at;
    p[i].wt = time - p[i].at;
    p[i].ct = time + p[i].bt;
    p[i].tat = p[i].wt + p[i].bt;

    time += p[i].bt;

    total_wt += p[i].wt;
    total_tat += p[i].tat;
  }

  printf("\nProcess\tArrival\tBurst\tWaiting\tTurnaround\n");
  for (int i = 0; i < n; i++)
  {
    printf("%d\t%d\t%d\t%d\t%d\n",
           p[i].pid, p[i].at, p[i].bt, p[i].wt, p[i].tat);
  }

  printf("\nAverage Waiting Time: %f\n", total_wt / n);
  printf("Average Turnaround Time: %f\n", total_tat / n);

  return 0;
}
