#include <stdio.h>

struct Processes {
    int ID, AT, BT, CT, TAT, WT, RT;
};

int main() {
    int n;
    printf("Enter number of processes: ");
    scanf("%d", &n);

    struct Processes p[n];
    for(int i = 0; i < n; i++) {
        p[i].ID = i + 1;
        printf("Arrival Time of P%d: ", p[i].ID);
        scanf("%d", &p[i].AT);

        printf("Burst Time of P%d: ", p[i].ID);
        scanf("%d", &p[i].BT);
    }

    // Sort by Arrival Time
    for(int i = 0; i < n-1; i++) {
        for(int j = 0; j < n-i-1; j++) {
            if(p[j].AT > p[j+1].AT) {
                struct Processes temp = p[j];
                p[j] = p[j+1];
                p[j+1] = temp;
            }
        }
    }

    int timePassed = 0, sumTAT = 0, sumWT = 0, sumRT = 0;
    for(int i = 0; i < n; i++) {
        if(timePassed < p[i].AT) timePassed = p[i].AT;

        p[i].CT = timePassed + p[i].BT;
        p[i].TAT = p[i].CT - p[i].AT;
        p[i].WT = p[i].TAT - p[i].BT;
        p[i].RT = p[i].WT;

        timePassed += p[i].BT;
        sumTAT += p[i].TAT;
        sumWT += p[i].WT;
        sumRT += p[i].RT;
    }

    printf("\nProcess\tAT\tBT\tCT\tTAT\tWT\tRT\n");
    for(int i = 0; i < n; i++) {
        printf("P%d\t%d\t%d\t%d\t%d\t%d\t%d\n",
               p[i].ID, p[i].AT, p[i].BT, p[i].CT,
               p[i].TAT, p[i].WT, p[i].RT);
    }

    printf("\nAverage TAT: %.2f\n", (float)sumTAT/n);
    printf("Average WT: %.2f\n", (float)sumWT/n);
    printf("Average RT: %.2f\n", (float)sumRT/n);

    return 0;
}

