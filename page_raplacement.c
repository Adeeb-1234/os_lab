#include <stdio.h>
#include <stdbool.h>

void simulate(int pages[], int n, int nf, char* name, int type) {
    int frames[20], time[20] = {0}, faults = 0;
    for (int i = 0; i < nf; i++) frames[i] = -1;

    printf("\n--- %s Simulation ---\n", name);
    for (int i = 0; i < n; i++) {
        bool hit = false;
        for (int j = 0; j < nf; j++) {
            if (frames[j] == pages[i]) { hit = true; break; }
        }

        if (hit) {
            printf("Page %d: HIT\n", pages[i]);
        } else {
            int idx = 0;
            for (int j = 0; j < nf; j++) {
                if (frames[j] == -1) { idx = j; break; } // Fill empty slots first

                if (type == 0 && j == faults % nf) {
                    idx = j; // FIFO
                } else if (type == 1 && time[j] < time[idx]) {
                    idx = j; // LRU
                } else if (type == 2) { // Optimal (Corrected)
                    int k, far = i, current_idx_far = -1;
                    for (int frame_j = 0; frame_j < nf; frame_j++) {
                        for (k = i + 1; k < n; k++) {
                            if (frames[frame_j] == pages[k]) break;
                        }
                        // If a page is never used again, it's the perfect candidate to replace
                        if (k == n) {
                            idx = frame_j;
                            break;
                        }
                        // Otherwise, track which page is used furthest in the future
                        if (k > current_idx_far) {
                            current_idx_far = k;
                            idx = frame_j;
                        }
                    }
                }
            }
            frames[idx] = pages[i];
            faults++;
            printf("Page %d: MISS (Fault)\n", pages[i]);
        }
        // Update access history for LRU tracking
        for (int j = 0; j < nf; j++) if (frames[j] == pages[i]) time[j] = i;
    }
    printf("Total Page Faults (%s): %d\n", name, faults);
}

int main() {
    int n, nf, pages[50];

    printf("Enter number of frames: ");
    scanf("%d", &nf);

    printf("Enter number of pages in reference string: ");
    scanf("%d", &n);

    printf("Enter the page reference string (separated by spaces): ");
    for (int i = 0; i < n; i++) {
        scanf("%d", &pages[i]);
    }

    simulate(pages, n, nf, "FIFO", 0);
    simulate(pages, n, nf, "LRU", 1);
    simulate(pages, n, nf, "Optimal", 2);

    return 0;
}
