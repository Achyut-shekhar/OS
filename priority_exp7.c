#include <stdio.h>

typedef struct
{
  int pid, at, bt, wt, tat, ct, priority, rt;
} Process;

int exec_order[200][3]; // start, end, pid
int log_index = 0;
float total_wt = 0, total_tat = 0;

// ================= Non-Preemptive Priority Scheduling =================
void nonPreemptivePriority(Process p[], int n)
{
  int completed = 0, curr_time = 0;
  int is_completed[n];
  for (int i = 0; i < n; i++)
    is_completed[i] = 0;

  while (completed < n)
  {
    int idx = -1, best_priority = 1e9;

    for (int i = 0; i < n; i++)
    {
      if (p[i].at <= curr_time && !is_completed[i])
      {
        if (p[i].priority < best_priority ||
            (p[i].priority == best_priority && p[i].at < p[idx].at))
        {
          best_priority = p[i].priority;
          idx = i;
        }
      }
    }

    if (idx != -1)
    {
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
      curr_time++;
  }
}

// ================= Preemptive Priority Scheduling =================
void preemptivePriority(Process p[], int n)
{
  int completed = 0, curr_time = 0;
  int is_completed[n];
  for (int i = 0; i < n; i++)
  {
    is_completed[i] = 0;
    p[i].rt = p[i].bt; // remaining time
  }

  int prev_pid = -1; // to track context switches

  while (completed < n)
  {
    int idx = -1, best_priority = 1e9;

    for (int i = 0; i < n; i++)
    {
      if (p[i].at <= curr_time && !is_completed[i])
      {
        if (p[i].priority < best_priority ||
            (p[i].priority == best_priority && p[i].at < p[idx].at))
        {
          best_priority = p[i].priority;
          idx = i;
        }
      }
    }

    if (idx != -1)
    {
      if (p[idx].pid != prev_pid)
      {
        exec_order[log_index][0] = curr_time;
        exec_order[log_index][2] = p[idx].pid;
        log_index++;
      }

      curr_time++;
      p[idx].rt--;

      exec_order[log_index - 1][1] = curr_time;
      prev_pid = p[idx].pid;

      if (p[idx].rt == 0)
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
      curr_time++;
  }
}

// ================= Results Printing =================
void printResults(Process p[], int n)
{
  printf("\nExecution Order:\n");
  for (int i = 0; i < log_index; i++)
  {
    printf("Time %d -> %d: Process P%d executed\n",
           exec_order[i][0], exec_order[i][1], exec_order[i][2]);
  }

  printf("\nGantt Chart:\n|");
  for (int i = 0; i < log_index; i++)
    printf("  P%d  |", exec_order[i][2]);
  printf("\n");

  printf("%d", exec_order[0][0]);
  for (int i = 0; i < log_index; i++)
    printf("      %d", exec_order[i][1]);
  printf("\n");

  printf("\nFinal Table:\n");
  printf("Process\tArrival\tBurst\tPriority\tWaiting\tTurnaround\tCompletion\n");
  for (int i = 0; i < n; i++)
  {
    printf("P%d\t%d\t%d\t%d\t\t%d\t%d\t\t%d\n",
           p[i].pid, p[i].at, p[i].bt, p[i].priority,
           p[i].wt, p[i].tat, p[i].ct);
  }

  printf("\nAverage Waiting Time: %.2f\n", total_wt / n);
  printf("Average Turnaround Time: %.2f\n", total_tat / n);
}

// ================= Main =================
int main()
{
  int n, choice;
  printf("Enter number of processes: ");
  scanf("%d", &n);

  Process p[n];
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
    p[i].rt = p[i].bt;
  }

  printf("Enter priorities (lower value = higher priority):\n");
  for (int i = 0; i < n; i++)
  {
    printf("P%d: ", i + 1);
    scanf("%d", &p[i].priority);
  }

  printf("\nChoose Scheduling Type:\n");
  printf("1. Non-preemptive Priority Scheduling\n");
  printf("2. Preemptive Priority Scheduling\n");
  printf("Enter choice: ");
  scanf("%d", &choice);

  switch (choice)
  {
  case 1:
    nonPreemptivePriority(p, n);
    break;
  case 2:
    preemptivePriority(p, n);
    break;
  default:
    printf("Invalid choice!\n");
    return 0;
  }

  printResults(p, n);
  return 0;
}
