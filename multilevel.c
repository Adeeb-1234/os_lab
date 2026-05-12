#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 100

typedef struct {
    int process_id;
    int arrival_time;
    int burst_time;
    int remaining_time;
    int completion_time;
    int waiting_time;
    int turnaround_time;
    char type[10]; // "system" or "user"
} Process;

typedef struct {
    Process queue[MAX];
    int front, rear;
} Queue;

void initQueue(Queue *q) {
    q->front = q->rear = -1;
}

int isEmpty(Queue *q) {
    return q->front == -1;
}

void enqueue(Queue *q, Process p) {
    if (q->rear == MAX - 1) return;
    if (q->front == -1) q->front = 0;
    q->queue[++q->rear] = p;
}

Process dequeueFCFS(Queue *q) {
    Process p = q->queue[q->front];
    if (q->front == q->rear) {
        q->front = q->rear = -1;
    } else {
        q->front++;
    }
    return p;
}

// For SJF: pick shortest job from userQueue
Process dequeueSJF(Queue *q) {
    int minIndex = q->front;
    for (int j = q->front; j <= q->rear; j++) {
        if (q->queue[j].remaining_time < q->queue[minIndex].remaining_time) {
            minIndex = j;
        }
    }
    Process p = q->queue[minIndex];
    for (int j = minIndex; j < q->rear; j++) {
        q->queue[j] = q->queue[j+1];
    }
    q->rear--;
    if (q->rear < q->front) q->front = q->rear = -1;
    return p;
}

int compareArrival(const void *a, const void *b) {
    Process *p1 = (Process *)a;
    Process *p2 = (Process *)b;
    return p1->arrival_time - p2->arrival_time;
}

int main() {
    int n;
    printf("Enter total number of processes: ");
    scanf("%d", &n);

    Process process_list[MAX];
    for (int i = 0; i < n; i++) {
        printf("Enter process_id, arrival_time, burst_time, type (system/user): ");
        scanf("%d %d %d %s", &process_list[i].process_id,
              &process_list[i].arrival_time,
              &process_list[i].burst_time,
              process_list[i].type);
        process_list[i].remaining_time = process_list[i].burst_time;
    }

    qsort(process_list, n, sizeof(Process), compareArrival);

    Queue systemQueue, userQueue;
    initQueue(&systemQueue);
    initQueue(&userQueue);

    int current_time = 0, completed = 0, i = 0;
    Process *current_process = NULL;

    // Timeline array for Gantt chart
    int timeline[MAX*10]; // enough slots
    int timeline_len = 0;

    while (completed < n) {
        // Add newly arrived processes
        while (i < n && process_list[i].arrival_time <= current_time) {
            if (strcmp(process_list[i].type, "system") == 0) {
                enqueue(&systemQueue, process_list[i]);
            } else {
                enqueue(&userQueue, process_list[i]);
            }
            i++;
        }

        // Preemption: system > user
        if (current_process != NULL) {
            if (strcmp(current_process->type, "user") == 0 && !isEmpty(&systemQueue)) {
                enqueue(&userQueue, *current_process);
                current_process = NULL;
            }
        }

        // Select next process
        if (current_process == NULL) {
            if (!isEmpty(&systemQueue)) {
                Process p = dequeueFCFS(&systemQueue);
                current_process = (Process *)malloc(sizeof(Process));
                *current_process = p;
            } else if (!isEmpty(&userQueue)) {
                Process p = dequeueSJF(&userQueue);
                current_process = (Process *)malloc(sizeof(Process));
                *current_process = p;
            } else {
                timeline[timeline_len++] = -1; // idle
                current_time++;
                continue;
            }
        }

        // Execute for 1 unit
        timeline[timeline_len++] = current_process->process_id;
        current_process->remaining_time--;
        current_time++;

        // Completion check
        if (current_process->remaining_time == 0) {
            current_process->completion_time = current_time;
            current_process->turnaround_time = current_process->completion_time - current_process->arrival_time;
            current_process->waiting_time = current_process->turnaround_time - current_process->burst_time;

            // Update original list
            for (int k = 0; k < n; k++) {
                if (process_list[k].process_id == current_process->process_id) {
                    process_list[k] = *current_process;
                    break;
                }
            }

            completed++;
            free(current_process);
            current_process = NULL;
        }
    }

    // Print Gantt Chart
    printf("\nGantt Chart:\n ");
    for (int t = 0; t < timeline_len; t++) {
        if (timeline[t] == -1)
            printf(" idle ");
        else
            printf(" P%d ", timeline[t]);
    }
    printf("\n0");
    for (int t = 1; t <= timeline_len; t++) {
        printf("   %d", t);
    }
    printf("\n");

    // Results
    double avgWT = 0, avgTAT = 0;
    printf("\nProcess\tAT\tBT\tCT\tTAT\tWT\tType\n");
    for (int j = 0; j < n; j++) {
        printf("P%d\t%d\t%d\t%d\t%d\t%d\t%s\n",
               process_list[j].process_id,
               process_list[j].arrival_time,
               process_list[j].burst_time,
               process_list[j].completion_time,
               process_list[j].turnaround_time,
               process_list[j].waiting_time,
               process_list[j].type);
        avgWT += process_list[j].waiting_time;
        avgTAT += process_list[j].turnaround_time;
    }

    printf("\nAverage Waiting Time = %.2f\n", avgWT/n);
    printf("Average Turnaround Time = %.2f\n", avgTAT/n);

    return 0;
}

