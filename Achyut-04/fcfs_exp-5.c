#include <stdio.h>

int main()
{
  printf("input number of processes: ");
  int n;
  scanf("%d", &n);

  int bt[n], at[n], wt[n], tat[n];
  float total_wt = 0, total_tat = 0;

  printf("input arrival times:\n");
  for (int i = 0; i < n; i++)
  {
    printf("process %d: ", i + 1);
    scanf("%d", &at[i]);
  }

  printf("input burst times:\n");
  for (int i = 0; i < n; i++)
  {
    printf("process %d: ", i + 1);
    scanf("%d", &bt[i]);
  }

  wt[0] = 0; // First process always has zero waiting time
  int completion_time = at[0] + bt[0];

  for (int i = 1; i < n; i++)
  {
    if (completion_time < at[i])
      completion_time = at[i];
    wt[i] = completion_time - at[i];
    if (wt[i] < 0) wt[i] = 0;
    completion_time += bt[i];
  }

  for (int i = 0; i < n; i++)
  {
    tat[i] = wt[i] + bt[i];
    total_wt += wt[i];
    total_tat += tat[i];
  }

  printf("\nProcess\tArrival Time\tBurst Time\tWaiting Time\tTurnaround Time\n");
  for (int i = 0; i < n; i++)
  {
    printf("%d\t%d\t\t%d\t\t%d\t\t%d\n", i + 1, at[i], bt[i], wt[i], tat[i]);
  }
  printf("\nAverage Waiting Time: %f\n", total_wt / n);
  printf("Average Turnaround Time: %f\n", total_tat / n);
  return 0;
}