#include <stdio.h>

struct Process {
    int id, at, bt, ct, tat, wt;
};

int main() {
    int n;
    printf("Enter number of processes: ");
    scanf("%d", &n);

    struct Process p[n];
    for (int i = 0; i < n; i++) {
        p[i].id = i + 1;
        printf("Arrival Time of P%d: ", p[i].id);
        scanf("%d", &p[i].at);
        printf("Burst Time of P%d: ", p[i].id);
        scanf("%d", &p[i].bt);
    }

    int completed = 0, time = 0;
    int sumTAT = 0, sumWT = 0;
    int isCompleted[n];
    for (int i = 0; i < n; i++) isCompleted[i] = 0;

    while (completed != n) {
        int idx = -1;
        int minBT = 1e9;

        // Find process with shortest burst time among arrived processes
        for (int i = 0; i < n; i++) {
            if (p[i].at <= time && !isCompleted[i]) {
                if (p[i].bt < minBT) {
                    minBT = p[i].bt;
                    idx = i;
                }
            }
        }

        if (idx != -1) {
            p[idx].ct = time + p[idx].bt;
            p[idx].tat = p[idx].ct - p[idx].at;
            p[idx].wt = p[idx].tat - p[idx].bt;

            sumTAT += p[idx].tat;
            sumWT += p[idx].wt;

            time += p[idx].bt;
            isCompleted[idx] = 1;
            completed++;
        } else {
            time++; // If no process has arrived yet, move time forward
        }
    }

    printf("\nProcess\tAT\tBT\tCT\tTAT\tWT\n");
    for (int i = 0; i < n; i++) {
        printf("P%d\t%d\t%d\t%d\t%d\t%d\n",
               p[i].id, p[i].at, p[i].bt, p[i].ct, p[i].tat, p[i].wt);
    }

    printf("\nAverage TAT: %.2f\n", (float)sumTAT / n);
    printf("Average WT: %.2f\n", (float)sumWT / n);

    return 0;
}


