#include<stdio.h>
#include<stdlib.h>

struct Process{
    int pid;
    int AT;
    int BT;
    int CT;
    int TAT;
    int WT;
};

int compareByBurst(const void *a,const void *b){
    return ((struct Process*)a)->BT-((struct Process *)b)->BT;
}

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

    // Sort all processes based on Burst Time
    qsort(p,n,sizeof(struct Process),compareByBurst);

    int currentTime = 0;
    float total_tat = 0;
    float total_wt = 0;

    // Calculate Completion Time for each process
    for (int i = 0; i < n; i++) {
        // This simple version assumes all processes arrive at time 0.
        // The logic is the same as FCFS after sorting.
        p[i].CT = currentTime + p[i].BT;
        p[i].TAT = p[i].CT - p[i].AT; // AT is 0 for this simple case
        p[i].WT = p[i].TAT - p[i].BT;

        currentTime = p[i].CT;

        total_tat += p[i].TAT;
        total_wt += p[i].WT;
    }

    // Print the final results table
    printf("\nPID\tAT\tBT\CT\tTAT\tWT\n");
    for(int i=0;i<n;i++){
        printf("%d\t%d\t%d\t%d\t%d\t%d\n",p[i].pid, p[i].AT, p[i].BT, p[i].CT, p[i].TAT, p[i].WT);
    }
    return 0;
}
