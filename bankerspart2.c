#include <stdio.h>
#include <stdbool.h>

// Function to check system safety
bool isSafe(int n, int m, int alloc[n][m], int need[n][m], int avail[m], int safeSeq[]) {
    int work[m];
    bool finish[n];

    for (int i = 0; i < m; i++)
        work[i] = avail[i];

    for (int i = 0; i < n; i++)
        finish[i] = false;

    int count = 0;

    while (count < n) {
        bool found = false;

        for (int i = 0; i < n; i++) {
            if (!finish[i]) {
                int j;
                for (j = 0; j < m; j++) {
                    if (need[i][j] > work[j])
                        break;
                }

                if (j == m) {
                    for (int k = 0; k < m; k++)
                        work[k] += alloc[i][k];

                    safeSeq[count++] = i;
                    finish[i] = true;
                    found = true;
                }
            }
        }

        if (!found)
            return false;
    }

    return true;
}

// Function for Resource Request Algorithm
bool requestResources(int n, int m, int alloc[n][m], int max[n][m], int need[n][m], int avail[m], int process, int request[]) {

    // Step 1: Check if request <= need
    for (int i = 0; i < m; i++) {
        if (request[i] > need[process][i]) {
            printf("Error: Process has exceeded its maximum claim.\n");
            return false;
        }
    }

    // Step 2: Check if request <= available
    for (int i = 0; i < m; i++) {
        if (request[i] > avail[i]) {
            printf("Resources not available. Process must wait.\n");
            return false;
        }
    }

    // Step 3: Pretend allocation
    for (int i = 0; i < m; i++) {
        avail[i] -= request[i];
        alloc[process][i] += request[i];
        need[process][i] -= request[i];
    }

    int safeSeq[n];

    // Step 4: Check safety
    if (isSafe(n, m, alloc, need, avail, safeSeq)) {
        printf("Request can be granted. System remains in safe state.\n");
        printf("Safe sequence: ");
        for (int i = 0; i < n - 1; i++)
            printf("P%d -> ", safeSeq[i]);
        printf("P%d\n", safeSeq[n - 1]);

        return true;
    } else {
        // Rollback if unsafe
        for (int i = 0; i < m; i++) {
            avail[i] += request[i];
            alloc[process][i] -= request[i];
            need[process][i] += request[i];
        }

        printf("Request cannot be granted. System would be unsafe.\n");
        return false;
    }
}

int main() {
    int n, m;

    printf("Enter number of processes: ");
    scanf("%d", &n);
    printf("Enter number of resources: ");
    scanf("%d", &m);

    int alloc[n][m], max[n][m], avail[m], need[n][m];

    printf("Enter Allocation Matrix:\n");
    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++)
            scanf("%d", &alloc[i][j]);

    printf("Enter Maximum Demand Matrix:\n");
    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++)
            scanf("%d", &max[i][j]);

    printf("Enter Available Resources:\n");
    for (int i = 0; i < m; i++)
        scanf("%d", &avail[i]);

    // Calculate Need matrix
    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++)
            need[i][j] = max[i][j] - alloc[i][j];

    int safeSeq[n];

    if (isSafe(n, m, alloc, need, avail, safeSeq)) {
        printf("\nSystem is in a safe state.\n");
        printf("Safe sequence: ");
        for (int i = 0; i < n - 1; i++)
            printf("P%d -> ", safeSeq[i]);
        printf("P%d\n", safeSeq[n - 1]);
    } else {
        printf("\nSystem is NOT in a safe state.\n");
    }

    // Resource Request
    int process;
    printf("\nEnter process number making request: ");
    scanf("%d", &process);

    int request[m];
    printf("Enter request vector:\n");
    for (int i = 0; i < m; i++)
        scanf("%d", &request[i]);

    requestResources(n, m, alloc, max, need, avail, process, request);

    return 0;
}
