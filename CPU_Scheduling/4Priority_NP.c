#include <stdio.h>
#include <stdlib.h>

// We add a 'priority' field to the struct
struct Process {
    int pid;
    int AT;
    int BT;
    int priority; // Lower number means higher priority
    int CT;
    int TAT;
    int WT;
};

// New comparison function to sort by priority
int compareByPriority(const void *a, const void *b) {
    return ((struct Process *)a)->priority - ((struct Process *)b)->priority;
}

int main() {
    int n;
    printf("Enter the number of processes: ");
    scanf("%d", &n);

    struct Process p[n];

    // Take user input for each process, including priority
    for (int i = 0; i < n; i++) {
        p[i].pid = i + 1;
        printf("Enter Arrival Time for P%d: ", i + 1);
        scanf("%d", &p[i].AT);
        printf("Enter Burst Time for P%d: ", i + 1);
        scanf("%d", &p[i].BT);
        printf("Enter Priority for P%d: ", i + 1);
        scanf("%d", &p[i].priority);
    }

    // Sort all processes based on Priority
    qsort(p, n, sizeof(struct Process), compareByPriority);

    int currentTime = 0;
    float total_tat = 0;
    float total_wt = 0;

    // Calculation logic is identical to FCFS/SJF
    for (int i = 0; i < n; i++) {
        if (currentTime < p[i].AT) {
            currentTime = p[i].AT;
        }

        p[i].CT = currentTime + p[i].BT;
        p[i].TAT = p[i].CT - p[i].AT;
        p[i].WT = p[i].TAT - p[i].BT;

        currentTime = p[i].CT;

        total_tat += p[i].TAT;
        total_wt += p[i].WT;
    }

    // Print the final results table
    printf("\nPID\tAT\tBT\tPriority\tCT\tTAT\tWT\n");
    for (int i = 0; i < n; i++) {
        printf("%d\t%d\t%d\t%d\t\t%d\t%d\t%d\n", p[i].pid, p[i].AT, p[i].BT, p[i].priority, p[i].CT, p[i].TAT, p[i].WT);
    }

    // Print the averages
    printf("\nAverage Turnaround Time: %.2f\n", total_tat / n);
    printf("Average Waiting Time: %.2f\n", total_wt / n);

    return 0;
}
