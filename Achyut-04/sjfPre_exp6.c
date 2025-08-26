
#include <stdio.h>

typedef struct
{
  int pid, at, bt, wt, tat, ct, remaining_bt;
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
    p[i].remaining_bt = p[i].bt;
  }

  int completed = 0, curr_time = 0, prev = -1;
  int is_completed[n];
  for (int i = 0; i < n; i++)
    is_completed[i] = 0;

  // Execution order log
  int exec_order[100][3]; // {start_time, end_time, pid}
  int log_index = 0;

  while (completed < n)
  {
    int idx = -1, min_bt = 1e9;
    for (int i = 0; i < n; i++)
    {
      if (p[i].at <= curr_time && !is_completed[i])
      {
        if (p[i].remaining_bt < min_bt)
        {
          min_bt = p[i].remaining_bt;
          idx = i;
        }
        if (p[i].remaining_bt == min_bt && p[i].at < p[idx].at)
        {
          idx = i;
        }
      }
    }

    if (idx != -1)
    {
      if (prev != idx)
      {
        if (prev != -1)
        {
          exec_order[log_index - 1][1] = curr_time; // end previous
        }
        exec_order[log_index][0] = curr_time; // start new
        exec_order[log_index][2] = p[idx].pid;
        log_index++;
      }

      p[idx].remaining_bt--;
      curr_time++;
      prev = idx;

      if (p[idx].remaining_bt == 0)
      {
        p[idx].ct = curr_time;
        p[idx].tat = p[idx].ct - p[idx].at;
        p[idx].wt = p[idx].tat - p[idx].bt;
        total_wt += p[idx].wt;
        total_tat += p[idx].tat;
        is_completed[idx] = 1;
        completed++;
      }
    }
    else
    {
      curr_time++;
    }
  }

  exec_order[log_index - 1][1] = curr_time; // close last

  // Print execution log
  printf("\nExecution Order:\n");
  for (int i = 0; i < log_index; i++)
  {
    printf("Time %d -> %d: Process P%d executed\n",
           exec_order[i][0], exec_order[i][1], exec_order[i][2]);
  }

  // Final table arranged according to execution
  printf("\nFinal Table (in execution order):\n");
  printf("Process\tArrival\tBurst\tWaiting\tTurnaround\tCompletion\n");
  int printed[100] = {0};
  for (int i = 0; i < log_index; i++)
  {
    int pid = exec_order[i][2];
    if (!printed[pid])
    {
      for (int j = 0; j < n; j++)
      {
        if (p[j].pid == pid)
        {
          printf("P%d\t%d\t%d\t%d\t%d\t\t%d\n",
                 p[j].pid, p[j].at, p[j].bt, p[j].wt,
                 p[j].tat, p[j].ct);
          printed[pid] = 1;
        }
      }
    }
  }

  printf("\nAverage Waiting Time: %.2f\n", total_wt / n);
  printf("Average Turnaround Time: %.2f\n", total_tat / n);

  return 0;
}
