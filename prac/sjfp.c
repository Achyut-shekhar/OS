#include<stdio.h>

typedef struct{
    int pid;
    int bt;
    int at;
    int wt;
    int ct;
    int tat;
    int remaining_bt;
    }    Process;

    int main(){
      int n,i, total_wt=0,total_tat=0;

      printf("input no. of proces ");
      scanf("%d",&n);
      Process p[n];
      int completed=0,curr_time=0;
      int is_completed[n];

      for(i=0;i<n;i++){
        printf("enter pid");
        scanf("%d",&p[i].pid);
        printf("enter bt");
        scanf("%d",&p[i].bt);
        p[i].remaining_bt=p[i].bt;
        printf("enter at");
        scanf("%d",&p[i].at);
        is_completed[i]=0;
      }

      while(completed<n){
        int idx=-1,min_bt=1e9;
        for(i=0;i<n;i++){
          if(p[i].at<=curr_time&&!is_completed[i]){
            if(p[i].remaining_bt<min_bt||p[i].remaining_bt==min_bt&&p[i].at<p[idx].at){
              min_bt=p[i].remaining_bt;
              idx=i;
            }
          }
        }

        if(idx!=-1){
          p[idx].remaining_bt--;
          curr_time++;
          if(p[idx].remaining_bt==0){
            p[idx].ct=curr_time;
            p[idx].tat=p[idx].ct-p[idx].at;
            p[idx].wt=p[idx].tat-p[idx].bt;
            total_wt+=p[idx].wt;
            total_tat+=p[idx].tat;
             is_completed[idx]=1;
             completed++;
          }
        }else{
          curr_time++;
        }
      }

      printf("pid\tbt\tat\tct\ttat\twt\n");
      for(i=0;i<n;i++){
        printf("%d\t%d\t%d\t%d\t%d\t%d\n",p[i].pid,p[i].bt,p[i].at,p[i].ct,p[i].tat,p[i].wt);
      }
      printf("average tat = %f\n",(float)total_tat/n);
      printf("average wt = %f\n",(float)total_wt/n);
    }