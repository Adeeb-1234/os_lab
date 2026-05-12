#include <stdio.h>
#include <stdbool.h>

int main() {
    int n, m, i, j, k;

    // Input from Page 2 & 3 of your document
    printf("Enter number of processes: "); // [cite: 38]
    scanf("%d", &n);
    printf("Enter number of resources: "); // [cite: 39]
    scanf("%d", &m);

    int alloc[n][m], max[n][m], avail[m], need[n][m];

    printf("Enter Allocation Matrix:\n"); // [cite: 40]
    for (i = 0; i < n; i++)
        for (j = 0; j < m; j++)
            scanf("%d", &alloc[i][j]);

    printf("Enter Maximum Demand Matrix:\n"); // [cite: 46]
    for (i = 0; i < n; i++)
        for (j = 0; j < m; j++)
            scanf("%d", &max[i][j]);

    printf("Enter Available Resources:\n"); // [cite: 52]
    for (i = 0; i < m; i++)
        scanf("%d", &avail[i]);

    // Calculate Need Matrix: Need[i][j] = Max[i][j] - Allocation[i][j] [cite: 27]
    for (i = 0; i < n; i++)
        for (j = 0; j < m; j++)
            need[i][j] = max[i][j] - alloc[i][j];

    // --- Safety Algorithm ---
    int work[m]; // [cite: 3]
    for (i = 0; i < m; i++) work[i] = avail[i];

    bool finish[n]; // [cite: 3]
    for (i = 0; i < n; i++) finish[i] = false;

    int safeSeq[n], ind = 0;

    for (k = 0; k < n; k++) {
        for (i = 0; i < n; i++) {
            if (finish[i] == false) { // [cite: 5]
                int flag = 0;
                for (j = 0; j < m; j++) {
                    if (need[i][j] > work[j]) { // [cite: 6]
                        flag = 1;
                        break;
                    }
                }

                if (flag == 0) { // If Need <= Work [cite: 6]
                    for (int y = 0; y < m; y++)
                        work[y] += alloc[i][y]; // [cite: 10]
                    finish[i] = true; // [cite: 11]
                    safeSeq[ind++] = i; // [cite: 13]
                }
            }
        }
    }

    // Output Result
    bool isSafe = true;
    for (i = 0; i < n; i++) {
        if (finish[i] == false) {
            isSafe = false;
            break;
        }
    }

    if (isSafe) {
        printf("\nSystem is in a safe state.\n"); // [cite: 16, 54]
        printf("Safe sequence is: "); // [cite: 17, 55]
        for (i = 0; i < n - 1; i++) printf("P%d -> ", safeSeq[i]);
        printf("P%d\n", safeSeq[n - 1]);
    } else {
        printf("\nSystem is in an UNSAFE STATE (Potential Deadlock).\n"); // [cite: 19]
    }

    return 0;
}
