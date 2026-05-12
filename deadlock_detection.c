#include <stdio.h>
#include <stdbool.h>

int main() {
    int n, m;

    // n = number of processes, m = number of resource types
    printf("Enter number of processes: ");
    scanf("%d", &n);
    printf("Enter number of resource types: ");
    scanf("%d", &m);

    int alloc[n][m], request[n][m], avail[m];
    bool finish[n];
    int deadlocked[n], count = 0;

    printf("\nEnter Allocation Matrix:\n");
    for (int i = 0; i < n; i++) {
        finish[i] = false; // Initialize all processes as not finished
        for (int j = 0; j < m; j++)
            scanf("%d", &alloc[i][j]);
    }

    printf("\nEnter Request Matrix:\n");
    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++)
            scanf("%d", &request[i][j]);

    printf("\nEnter Available Resources:\n");
    for (int i = 0; i < m; i++)
        scanf("%d", &avail[i]);

    // Detection Logic
    for (int k = 0; k < n; k++) {
        for (int i = 0; i < n; i++) {
            if (!finish[i]) {
                bool canBeDone = true;
                for (int j = 0; j < m; j++) {
                    if (request[i][j] > avail[j]) {
                        canBeDone = false;
                        break;
                    }
                }

                if (canBeDone) {
                    for (int j = 0; j < m; j++)
                        avail[j] += alloc[i][j];
                    finish[i] = true;
                }
            }
        }
    }

    // Check for unfinished processes
    for (int i = 0; i < n; i++) {
        if (!finish[i]) {
            deadlocked[count++] = i;
        }
    }

    if (count > 0) {
        printf("\nSystem is in DEADLOCK. Deadlocked processes: ");
        for (int i = 0; i < count; i++)
            printf("P%d ", deadlocked[i]);
        printf("\n");
    } else {
        printf("\nNo Deadlock Detected!\n");
    }

    return 0;
}
