#include <stdio.h>

#define N 3        // number of processes
#define MAX 100
int timeQuantum = 4;

// Status of process
enum Status { READY, RUNNING, FINISHED };

struct Process {
    int pid;
    int AT;      // Arrival Time
    int BT;      // Burst Time
    int RBT;     // Remaining Burst Time
    int CT;      // Completion Time
    int TAT;     // Turnaround Time
    int WT;      // Waiting Time
    enum Status s;
};

// Queue structure
struct Queue {
    int items[MAX];
    int front;
    int rear;
};

void enqueue(struct Queue *q, int val) {
    q->items[q->rear++] = val;
}

int dequeue(struct Queue *q) {
    return q->items[q->front++];
}

int isEmpty(struct Queue *q) {
    return q->front == q->rear;
}

int main() {
    // Example processes
    struct Process p[N] = {
        {1, 0, 5, 5, 0, 0, 0, READY},
        {2, 1, 3, 3, 0, 0, 0, READY},
        {3, 2, 8, 8, 0, 0, 0, READY}
    };

    struct Queue q;
    q.front = q.rear = 0;

    int currentTime = 0;
    int completed = 0;

    // Initially enqueue processes that arrive at time 0
    for (int i = 0; i < N; i++) {
        if (p[i].AT == 0) {
            enqueue(&q, i);
            p[i].s = RUNNING;
        }
    }

    // Main Round Robin loop
    while (completed < N) {
        if (isEmpty(&q)) {
            currentTime++;  // CPU idle
            // check arrivals
            for (int i = 0; i < N; i++) {
                if (p[i].AT <= currentTime && p[i].s == READY) {
                    enqueue(&q, i);
                    p[i].s = RUNNING;
                }
            }
            continue;
        }

        int idx = dequeue(&q);

        // Calculate execution time
        int runTime = (p[idx].RBT > timeQuantum) ? timeQuantum : p[idx].RBT;

        // Run the process
        currentTime += runTime;
        p[idx].RBT -= runTime;

        // Check new arrivals during this run
        for (int i = 0; i < N; i++) {
            if (p[i].AT <= currentTime && p[i].s == READY) {
                enqueue(&q, i);
                p[i].s = RUNNING;
            }
        }

        if (p[idx].RBT == 0) {
            // Finished
            p[idx].CT = currentTime;
            p[idx].TAT = p[idx].CT - p[idx].AT;
            p[idx].WT = p[idx].TAT - p[idx].BT;
            p[idx].s = FINISHED;
            completed++;
        } else {
            // Not finished, put back
            enqueue(&q, idx);
        }
    }

    // Print results
    printf("PID\tAT\tBT\tCT\tTAT\tWT\n");
    for (int i = 0; i < N; i++) {
        printf("%d\t%d\t%d\t%d\t%d\t%d\n",
               p[i].pid, p[i].AT, p[i].BT,
               p[i].CT, p[i].TAT, p[i].WT);
    }

    return 0;
}
