#include <stdio.h>

#define MAX 10

typedef struct {
    int id, bt, deadline, period, share;
    int ct, wt, tat;
    int remaining;
} Process;

int gcd(int a, int b) {
    while (b) {
        int t = b;
        b = a % b;
        a = t;
    }
    return a;
}

int lcm(int a, int b) {
    return (a * b) / gcd(a, b);
}

int hyperperiod(Process p[], int n) {
    int hp = p[0].period;
    for (int i = 1; i < n; i++)
        hp = lcm(hp, p[i].period);
    return hp;
}

void edf(Process p[], int n) {
    Process temp[MAX];
    for (int i = 0; i < n; i++) temp[i] = p[i];

    for (int i = 0; i < n - 1; i++)
        for (int j = i + 1; j < n; j++)
            if (temp[i].deadline > temp[j].deadline) {
                Process t = temp[i];
                temp[i] = temp[j];
                temp[j] = t;
            }

    int time = 0;
    printf("\n===== Earliest Deadline First (EDF) =====\n");
    printf("Gantt Chart:\n|");

    for (int i = 0; i < n; i++) {
        printf(" P%d |", temp[i].id);
        time += temp[i].bt;
        temp[i].ct = time;
        temp[i].tat = temp[i].ct;
        temp[i].wt = temp[i].tat - temp[i].bt;
    }

    printf("\n0");
    time = 0;
    for (int i = 0; i < n; i++) {
        time += temp[i].bt;
        printf("   %d", time);
    }

    printf("\n\nID BT Deadline CT WT TAT\n");
    for (int i = 0; i < n; i++) {
        printf("%d  %d   %d      %d  %d  %d\n",
               temp[i].id, temp[i].bt, temp[i].deadline,
               temp[i].ct, temp[i].wt, temp[i].tat);
    }
}

void rms(Process p[], int n) {
    Process temp[MAX];
    for (int i = 0; i < n; i++) temp[i] = p[i];

    for (int i = 0; i < n - 1; i++)
        for (int j = i + 1; j < n; j++)
            if (temp[i].period > temp[j].period) {
                Process t = temp[i];
                temp[i] = temp[j];
                temp[j] = t;
            }

    int time = 0;
    printf("\n===== Rate Monotonic Scheduling (RMS) =====\n");
    printf("Gantt Chart:\n|");

    for (int i = 0; i < n; i++) {
        printf(" P%d |", temp[i].id);
        time += temp[i].bt;
        temp[i].ct = time;
        temp[i].tat = temp[i].ct;
        temp[i].wt = temp[i].tat - temp[i].bt;
    }

    printf("\n0");
    time = 0;
    for (int i = 0; i < n; i++) {
        time += temp[i].bt;
        printf("   %d", time);
    }

    printf("\n\nID BT Period CT WT TAT\n");
    for (int i = 0; i < n; i++) {
        printf("%d  %d   %d     %d  %d  %d\n",
               temp[i].id, temp[i].bt, temp[i].period,
               temp[i].ct, temp[i].wt, temp[i].tat);
    }
}


int main() {
    int n;
    Process p[MAX];

    printf("Enter number of processes: ");
    scanf("%d", &n);

    for (int i = 0; i < n; i++) {
        p[i].id = i;

        printf("\nProcess %d:\n", i);

        printf("Burst Time: ");
        scanf("%d", &p[i].bt);

        printf("Deadline (for EDF): ");
        scanf("%d", &p[i].deadline);

        printf("Period (for RMS): ");
        scanf("%d", &p[i].period);


    }

    edf(p, n);
    rms(p, n);



    return 0;
}

