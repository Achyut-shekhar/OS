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
  // sorting according to the arrival time
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
  // calculating waiting time, turnaround time, and completion time
  int completed = 0, curr_time = 0, min_bt, idx;
  int is_completed[n];
  for (int i = 0; i < n; i++)
    is_completed[i] = 0;

  while (completed < n) {
    min_bt = 1e9;
    idx = -1;
    for (int i = 0; i < n; i++) {
      if (p[i].at <= curr_time && !is_completed[i]) {
        if (p[i].bt < min_bt) {
          min_bt = p[i].bt;
          idx = i;
        }
      }
    }
    if (idx == -1) {
      curr_time++;
    } else {
      p[idx].wt = curr_time - p[idx].at;
      if (p[idx].wt < 0) p[idx].wt = 0;
      p[idx].ct = curr_time + p[idx].bt;
      p[idx].tat = p[idx].ct - p[idx].at;
      total_wt += p[idx].wt;
      total_tat += p[idx].tat;
      curr_time = p[idx].ct;
      is_completed[idx] = 1;
      completed++;
    }
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
