#include<stdio.h>
#include<stdlib.h>

struct process{
    int pid;
    int AT;
    int BT;
    int CT;
    int TAT;
    int WT;
};

int compareByArrival(const void *a,const void *b)
{
    return((struct process*)a)->AT-((struct process*)b)->AT;
}

int main()
{
    int n;
    printf("Enter num of processes: ");
    scanf("%d",&n);

    struct process p[n];

    for(int i=0;i<n;i++){
        p[i].pid=i+1;
        printf("Enter Arrival Time for P%d: ", i + 1);
        scanf("%d", &p[i].AT);
        printf("Enter Burst Time for P%d: ", i + 1);
        scanf("%d", &p[i].BT);
    }

    qsort(p,n,sizeof(struct process),compareByArrival);
    int currTime=0;
    double total_tat=0,total_wt=0;
    for(int i=0;i<n;i++){
        if(currTime<p[i].AT){
            currTime=p[i].AT;
        }

        p[i].CT=currTime+p[i].BT;
        p[i].TAT=p[i].CT-p[i].AT;
        p[i].WT=p[i].TAT-p[i].BT;

        currTime=p[i].CT;
        total_tat=p[i].TAT;
        total_wt=p[i].WT;
    }

    printf("\nPID\tAT\tBT\tCT\tTAT\tWT\n");
    for (int i = 0; i < n; i++) {
        printf("%d\t%d\t%d\t%d\t%d\t%d\n", p[i].pid, p[i].AT, p[i].BT, p[i].CT, p[i].TAT, p[i].WT);
    }
    printf("\nAverage Turnaround Time: %.2f\n", total_tat / n);
    printf("Average Waiting Time: %.2f\n", total_wt / n);
    return 0;
}
