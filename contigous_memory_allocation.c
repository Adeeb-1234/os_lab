#include <stdio.h>

void simulate(int b[], int m, int p[], int n, char* name, int mode) {
    int alloc[20], blocks[20];
    for (int i = 0; i < m; i++) blocks[i] = b[i];
    for (int i = 0; i < n; i++) alloc[i] = -1;

    for (int i = 0; i < n; i++) {
        int idx = -1;
        for (int j = 0; j < m; j++) {
            if (blocks[j] >= p[i]) {
                if (mode == 0) { idx = j; break; } // First Fit
                if (mode == 1 && (idx == -1 || blocks[j] < blocks[idx])) idx = j; // Best Fit
                if (mode == 2 && (idx == -1 || blocks[j] > blocks[idx])) idx = j; // Worst Fit
            }
        }
        if (idx != -1) { alloc[i] = idx; blocks[idx] -= p[i]; }
    }

    printf("\n--- %s ---\nProc\tSize\tBlock\n", name);
    for (int i = 0; i < n; i++)
        printf("%d\t%d\t%s\n", i+1, p[i], alloc[i] != -1 ? (char[]){alloc[i]+'1', 0} : "None");
}

int main() {
    int m, n, b[20], p[20];
    printf("Enter # Blocks & Sizes: "); scanf("%d", &m);
    for (int i = 0; i < m; i++) scanf("%d", &b[i]);
    printf("Enter # Procs & Sizes: "); scanf("%d", &n);
    for (int i = 0; i < n; i++) scanf("%d", &p[i]);

    simulate(b, m, p, n, "FIRST FIT", 0);
    simulate(b, m, p, n, "BEST FIT", 1);
    simulate(b, m, p, n, "WORST FIT", 2);
    return 0;
}
