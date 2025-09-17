#include<stdio.h>
#include<stdlib.h>

struct Process{
    int pid;
    int AT;
    int BT;
    int RBT;
    int CT;
    int TAT;
    int WT;
};



int main() {
    int n;
    printf("Enter the number of processes: ");
    scanf("%d", &n);

    struct Process p[n];

    // Take user input for each process
    for (int i = 0; i < n; i++) {
        p[i].pid = i + 1;
        printf("Enter Arrival Time for P%d: ", i + 1);
        scanf("%d", &p[i].AT); // Note: AT is not used in this simple version
        printf("Enter Burst Time for P%d: ", i + 1);
        scanf("%d", &p[i].BT);
    }
    int currTime=0;
    double total_tat=0,total_wt=0;
    int completedProcess=0;

    while(completedProcess<currTime){
        int shortestJobId=-1;
        int minRBT=99999;

        for(int i=0;i<n;i++){
            if(p[i].AT<=currTime && p[i].RBT>0){
                if(p[i].RBT<minRBT){
                    minRBT=p[i].RBT;
                    shortestJobId=i;
                }
                if(p[i].RBT==minRBT){
                    if(p[i].AT<p[shortestJobId].AT){
                        shortestJobId=i;
                    }
                }
            }
        }

        if(shortestJobId!=-1){
            p[shortestJobId].RBT--;
            if(p[shortestJobId].RBT==0){
                completedProcess++;
                p[shortestJobId].CT=currTime+1;
                p[shortestJobId].TAT=p[shortestJobId].CT-p[shortestJobId].AT;
                p[shortestJobId].WT=p[shortestJobId].TAT-p[shortestJobId].BT;
                total_tat += p[shortestJobId].TAT;
                total_wt += p[shortestJobId].WT;
            }
        }
        currTime++;//updates each second;
    }

     printf("\nPID\tAT\tBT\tCT\tTAT\tWT\n");
    for (int i = 0; i < n; i++) {
        printf("%d\t%d\t%d\t%d\t%d\t%d\n", p[i].pid, p[i].AT, p[i].BT, p[i].CT, p[i].TAT, p[i].WT);
    }

    // Print the averages
    printf("\nAverage Turnaround Time: %.2f\n", total_tat / n);
    printf("Average Waiting Time: %.2f\n", total_wt / n);

    return 0;
}
