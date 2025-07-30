#include <stdio.h>
#include <stdbool.h>

#define MAX_PROCESSES 10
#define MAX_RESOURCES 10

int main() {
    int n, m, i, j, p;

    // Data structures
    int priority[MAX_PROCESSES];
    int max[MAX_PROCESSES][MAX_RESOURCES];
    int alloc[MAX_PROCESSES][MAX_RESOURCES] = {0};
    int avail[MAX_RESOURCES];
    bool waiting[MAX_PROCESSES] = {false};

    // Input counts
    printf("Enter number of processes: ");
    scanf("%d", &n);
    printf("Enter number of resource types: ");
    scanf("%d", &m);

    // Input priorities (0 = highest)
    printf("Enter priorities for each process (0 = highest):\n");
    for (i = 0; i < n; i++) {
        printf("P%d priority: ", i);
        scanf("%d", &priority[i]);
    }

    // Input max requirement matrix
    printf("Enter Max requirement matrix (%dx%d):\n", n, m);
    for (i = 0; i < n; i++)
        for (j = 0; j < m; j++)
            scanf("%d", &max[i][j]);

    // Input available resources
    printf("Enter Available resources (length %d):\n", m);
    for (j = 0; j < m; j++)
        scanf("%d", &avail[j]);

    // Process requests until user quits
    while (true) {
        printf("\nEnter process number making a request (or -1 to exit): ");
        scanf("%d", &p);
        if (p < 0 || p >= n) break;

        int req[MAX_RESOURCES];
        printf("Enter request vector for P%d:\n", p);
        for (j = 0; j < m; j++)
            scanf("%d", &req[j]);

        // Check if request ≤ max – alloc
        bool legal = true;
        for (j = 0; j < m; j++) {
            if (req[j] + alloc[p][j] > max[p][j]) {
                legal = false;
                break;
            }
        }
        if (!legal) {
            printf("Error: request exceeds declared maximum.\n");
            continue;
        }

        // Can we allocate directly?
        bool direct = true;
        for (j = 0; j < m; j++) {
            if (req[j] > avail[j]) {
                direct = false;
                break;
            }
        }

        if (!direct) {
            // Preempt all lower‑priority processes
            for (i = 0; i < n; i++) {
                if (!waiting[i] && priority[i] > priority[p]) {
                    printf("Preempting P%d (lower priority %d > %d)\n",
                           i, priority[i], priority[p]);
                    for (j = 0; j < m; j++) {
                        avail[j] += alloc[i][j];
                        alloc[i][j] = 0;
                    }
                    waiting[i] = true;
                }
            }
        }

        // Now allocate
        bool ok = true;
        for (j = 0; j < m; j++) {
            if (req[j] > avail[j]) ok = false;
        }
        if (!ok) {
            printf("Still insufficient resources after preemption. P%d must wait.\n", p);
            waiting[p] = true;
        } else {
            for (j = 0; j < m; j++) {
                avail[j] -= req[j];
                alloc[p][j] += req[j];
            }
            waiting[p] = false;
            printf("Allocated to P%d. Available now: ", p);
            for (j = 0; j < m; j++) printf("%d ", avail[j]);
            printf("\n");
        }
    }

    printf("Exiting.\n");
    return 0;
}

// Enter number of processes: 3
// Enter number of resource types: 2

// Enter priorities for each process (0 = highest):
// P0 priority: 1
// P1 priority: 0
// P2 priority: 2

// Enter Max requirement matrix (3x2):
// P0: 0 2
// P1: 1 1
// P2: 2 2

// Enter Available resources (length 2):
// 1 1

// --- Begin requests ---

// Enter process number making a request (or -1 to exit): 2
// Enter request vector for P2:
// 1 0
// Allocated to P2. Available now: 0 1

// Enter process number making a request (or -1 to exit): 0
// Enter request vector for P0:
// 0 1
// Allocated to P0. Available now: 0 0

// Enter process number making a request (or -1 to exit): 1
// Enter request vector for P1:
// 1 1
// Preempting P0 (lower priority 1 > 0)
// Preempting P2 (lower priority 2 > 0)
// Allocated to P1. Available now: 0 0

// Enter process number making a request (or -1 to exit): -1
// Exiting.
