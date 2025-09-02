#include <stdio.h>

typedef struct
{
  int pid, at, bt, wt, tat, ct;
} Process;

int main()
{
  printf("\n\t\t\t\t\tNAME: ACHYUT SHEKHAR SINGH | SECTION: C (G1) | ROLL NUMBER: 04\n");

  int n;
  printf("Enter number of processes: ");
  scanf("%d", &n);

  Process p[n];
  int is_completed[n];
  for (int i = 0; i < n; i++)
    is_completed[i] = 0;

  printf("Enter arrival times:\n");
  for (int i = 0; i < n; i++)
  {
    p[i].pid = i + 1;
    printf("P%d: ", i + 1);
    scanf("%d", &p[i].at);
  }

  printf("Enter burst times:\n");
  for (int i = 0; i < n; i++)
  {
    printf("P%d: ", i + 1);
    scanf("%d", &p[i].bt);
  }

  int completed = 0, curr_time = 0;
  float total_wt = 0, total_tat = 0;

  // Execution log
  int exec_order[100][3]; // start, end, pid
  int log_index = 0;

  while (completed < n)
  {
    int idx = -1, min_bt = 1e9;

    // Find the process with min burst among arrived
    for (int i = 0; i < n; i++)
    {
      if (p[i].at <= curr_time && !is_completed[i])
      {
        if (p[i].bt < min_bt)
        {
          min_bt = p[i].bt;
          idx = i;
        }
        else if (p[i].bt == min_bt && p[i].at < p[idx].at)
        {
          idx = i; // tie breaker
        }
      }
    }

    if (idx != -1)
    {
      // Process runs completely (non-preemptive)
      exec_order[log_index][0] = curr_time;
      exec_order[log_index][1] = curr_time + p[idx].bt;
      exec_order[log_index][2] = p[idx].pid;
      log_index++;

      curr_time += p[idx].bt;
      p[idx].ct = curr_time;
      p[idx].tat = p[idx].ct - p[idx].at;
      p[idx].wt = p[idx].tat - p[idx].bt;

      total_wt += p[idx].wt;
      total_tat += p[idx].tat;
      is_completed[idx] = 1;
      completed++;
    }
    else
    {
      curr_time++; // idle
    }
  }

  // Print execution log
  printf("\nExecution Order:\n");
  for (int i = 0; i < log_index; i++)
  {
    printf("Time %d -> %d: Process P%d executed\n",
           exec_order[i][0], exec_order[i][1], exec_order[i][2]);
  }

  // Print Gantt chart
  printf("\nGantt Chart:\n|");
  for (int i = 0; i < log_index; i++)
  {
    printf("  P%d  |", exec_order[i][2]);
  }
  printf("\n");

  // Time scale
  printf("%d", exec_order[0][0]);
  for (int i = 0; i < log_index; i++)
  {
    printf("      %d", exec_order[i][1]);
  }
  printf("\n");

  // Final table
  printf("\nFinal Table:\n");
  printf("Process\tArrival\tBurst\tWaiting\tTurnaround\tCompletion\n");
  for (int i = 0; i < n; i++)
  {
    printf("P%d\t%d\t%d\t%d\t%d\t\t%d\n",
           p[i].pid, p[i].at, p[i].bt, p[i].wt, p[i].tat, p[i].ct);
  }

  printf("\nAverage Waiting Time: %.2f\n", total_wt / n);
  printf("Average Turnaround Time: %.2f\n", total_tat / n);

  return 0;
}
