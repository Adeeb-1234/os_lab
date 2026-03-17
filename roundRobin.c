#include <stdio.h>

struct Process {
    int pid;
    int at;
    int bt;
    int rt;
    int wt;
    int tat;
    int ct;
};

int main() {
    int n, quantum;
    printf("Enter number of processes: ");
    scanf("%d", &n);

    struct Process p[n];
    for (int i = 0; i < n; i++) {
        p[i].pid = i + 1;
        printf("Enter arrival time for process %d: ", p[i].pid);
        scanf("%d", &p[i].at);
        printf("Enter burst time for process %d: ", p[i].pid);
        scanf("%d", &p[i].bt);
        p[i].rt = p[i].bt;
    }

    printf("Enter time quantum: ");
    scanf("%d", &quantum);

    int time = 0, done, gc[100], gcTime[100], gcIndex = 0;
    int completed = 0;

    while (completed < n) {
        done = 1;
        for (int i = 0; i < n; i++) {
            if (p[i].rt > 0 && p[i].at <= time) {
                done = 0;
                if (p[i].rt > quantum) {
                    time += quantum;
                    p[i].rt -= quantum;
                    gc[gcIndex] = p[i].pid;
                    gcTime[gcIndex++] = time;
                } else {
                    time += p[i].rt;
                    p[i].ct = time;
                    p[i].wt = p[i].ct - p[i].at - p[i].bt;
                    p[i].tat = p[i].ct - p[i].at;
                    p[i].rt = 0;
                    completed++;
                    gc[gcIndex] = p[i].pid;
                    gcTime[gcIndex++] = time;
                }
            }
        }
        if (done == 1) {
            time++;
        }
    }

    printf("\nProcess\tAT\tBT\tWT\tTAT\tCT\n");
    for (int i = 0; i < n; i++) {
        printf("P%d\t%d\t%d\t%d\t%d\t%d\n", p[i].pid, p[i].at, p[i].bt, p[i].wt, p[i].tat, p[i].ct);
    }

    float avgWT = 0, avgTAT = 0;
    for (int i = 0; i < n; i++) {
        avgWT += p[i].wt;
        avgTAT += p[i].tat;
    }
    avgWT /= n;
    avgTAT /= n;

    printf("\nAverage Waiting Time = %.2f", avgWT);
    printf("\nAverage Turnaround Time = %.2f\n", avgTAT);

    printf("\nGantt Chart:\n");
    printf("0");
    for (int i = 0; i < gcIndex; i++) {
        printf(" --P%d-- %d", gc[i], gcTime[i]);
    }
    printf("\n");

    return 0;
}
