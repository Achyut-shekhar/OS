#include <stdio.h>

typedef struct
{
  int pid;
  int bt;
  int at;
  int wt;
  int ct;
  int tat;
  

} Process;

int main()
{
  int n, i, total_wt = 0, total_tat = 0;

  printf("input no. of proces ");
  scanf("%d", &n);
  Process p[n];
  int completed = 0, curr_time = 0;
  int is_completed[n];

  for (i = 0; i < n; i++)
  {
    printf("enter pid");
    scanf("%d", &p[i].pid);
    printf("enter bt");
    scanf("%d", &p[i].bt);

    printf("enter at");
    scanf("%d", &p[i].at);

    is_completed[i] = 0;
  }



  printf("pid\tbt\tat\tct\ttat\twt\n");
  for (i = 0; i < n; i++)
  {
    printf("%d\t%d\t%d\t%d\t%d\t%d\n", p[i].pid, p[i].bt, p[i].at, p[i].ct, p[i].tat, p[i].wt);
  }
  printf("average tat = %f\n", (float)total_tat / n);
  printf("average wt = %f\n", (float)total_wt / n);
}