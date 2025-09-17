#include <stdio.h>
#include <string.h>

#define MAX 100
#define QUANTUM 20  // Time quantum in ns

struct Process {
    char name[20];
    int burstTime;
    int remainingTime;
    int consumedTime;
};

int main() {
    int n;
    struct Process processes[MAX];
    int queue[MAX];
    int front = 0, rear = 0;

    printf("Enter number of processes: ");
    scanf("%d", &n);

    for (int i = 0; i < n; i++) {
        printf("Enter name of process %d: ", i + 1);
        scanf("%s", processes[i].name);
        printf("Enter burst time (in ns) for %s: ", processes[i].name);
        scanf("%d", &processes[i].burstTime);
        processes[i].remainingTime = processes[i].burstTime;
        processes[i].consumedTime = 0;
        queue[rear++] = i;
    }

    printf("\nRound Robin Scheduling (Quantum = %d ns)\n", QUANTUM);

    while (front < rear) {
        int idx = queue[front++];
        int timeSlice = (processes[idx].remainingTime >= QUANTUM) ? QUANTUM : processes[idx].remainingTime;

        processes[idx].remainingTime -= timeSlice;
        processes[idx].consumedTime += timeSlice;

        printf("Process: %s | Remaining Time: %d ns | Total Consumed Time: %d ns\n",
               processes[idx].name, processes[idx].remainingTime, processes[idx].consumedTime);

        if (processes[idx].remainingTime > 0) {
            queue[rear++] = idx;
        }
    }

    printf("\nAll processes finished.\n");
    return 0;
}
