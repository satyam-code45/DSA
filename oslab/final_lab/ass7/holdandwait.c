#include <stdio.h>
#include <stdbool.h>

#define MAX_PROCESSES 10
#define MAX_RESOURCES 10

int main() {
    int n, m; // number of processes and resource types
    int max[MAX_PROCESSES][MAX_RESOURCES]; // max resource need
    int alloc[MAX_PROCESSES][MAX_RESOURCES] = {0}; // resources currently allocated
    int avail[MAX_RESOURCES]; // available resources
    bool finished[MAX_PROCESSES] = {false};

    printf("Enter number of processes: ");
    scanf("%d", &n);
    printf("Enter number of resource types: ");
    scanf("%d", &m);

    printf("Enter Available Resources (space-separated):\n");
    for (int i = 0; i < m; i++) {
        scanf("%d", &avail[i]);
    }

    printf("Enter Max resource requirement matrix (%d x %d):\n", n, m);
    for (int i = 0; i < n; i++) {
        printf("Process P%d: ", i);
        for (int j = 0; j < m; j++) {
            scanf("%d", &max[i][j]);
        }
    }

    printf("\n--- Resource Allocation Begins ---\n");

    int completed = 0;
    while (completed < n) {
        bool allocated_this_round = false;

        for (int i = 0; i < n; i++) {
            if (!finished[i]) {
                bool can_allocate = true;

                for (int j = 0; j < m; j++) {
                    if (max[i][j] > avail[j]) {
                        can_allocate = false;
                        break;
                    }
                }

                if (can_allocate) {
                    printf("Process P%d is allocated resources: ", i);
                    for (int j = 0; j < m; j++) {
                        avail[j] -= max[i][j];
                        alloc[i][j] = max[i][j];
                        printf("%d ", alloc[i][j]);
                    }
                    printf("\nProcess P%d is executing...\n", i);

                    // Simulate execution and resource release
                    for (int j = 0; j < m; j++) {
                        avail[j] += alloc[i][j];
                        alloc[i][j] = 0;
                    }

                    printf("Process P%d has finished and released resources.\n\n", i);
                    finished[i] = true;
                    completed++;
                    allocated_this_round = true;
                }
            }
        }

        if (!allocated_this_round) {
            printf("No further allocation possible. System might be in unsafe state.\n");
            break;
        }
    }

    if (completed == n) {
        printf("All processes executed without Hold and Wait. System is safe.\n");
    }

    return 0;
}

// Enter number of processes: 3
// Enter number of resource types: 2
// Enter Available Resources:
// 3 3
// Enter Max resource requirement matrix:
// Process P0: 1 2
// Process P1: 2 1
// Process P2: 3 3
