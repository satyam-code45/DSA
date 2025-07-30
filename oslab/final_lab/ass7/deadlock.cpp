#include <stdio.h>

#define MAX_PROCESSES 10
#define MAX_RESOURCES 10

int main() {
    int n, m, i, j, k;
    int alloc[MAX_PROCESSES][MAX_RESOURCES];
    int max[MAX_PROCESSES][MAX_RESOURCES];
    int need[MAX_PROCESSES][MAX_RESOURCES];
    int avail[MAX_RESOURCES];
    int finish[MAX_PROCESSES];
    int safe_seq[MAX_PROCESSES];

    // Input number of processes and resources
    printf("Enter the number of processes: ");
    scanf("%d", &n);
    printf("Enter the number of resource types: ");
    scanf("%d", &m);

    // Input Allocation matrix
    printf("Enter Allocation Matrix (%d x %d):\n", n, m);
    for (i = 0; i < n; i++)
        for (j = 0; j < m; j++)
            scanf("%d", &alloc[i][j]);

    // Input Max matrix
    printf("Enter Max Matrix (%d x %d):\n", n, m);
    for (i = 0; i < n; i++)
        for (j = 0; j < m; j++)
            scanf("%d", &max[i][j]);

    // Input Available vector
    printf("Enter Available Resources (length %d):\n", m);
    for (i = 0; i < m; i++)
        scanf("%d", &avail[i]);

    // Calculate Need matrix
    for (i = 0; i < n; i++)
        for (j = 0; j < m; j++)
            need[i][j] = max[i][j] - alloc[i][j];

    // Initialize Finish flags
    for (i = 0; i < n; i++)
        finish[i] = 0;

    // Safety algorithm
    int count = 0;
    while (count < n) {
        int found = 0;
        for (i = 0; i < n; i++) {
            if (!finish[i]) {
                // Check if need[i] <= avail
                for (j = 0; j < m; j++)
                    if (need[i][j] > avail[j])
                        break;
                if (j == m) {
                    // Simulate allocation
                    for (k = 0; k < m; k++)
                        avail[k] += alloc[i][k];
                    safe_seq[count++] = i;
                    finish[i] = 1;
                    found = 1;
                }
            }
        }
        if (!found) {
            printf("System is NOT in a safe state.\n");
            return 0;
        }
    }

    // If here, system is safe
    printf("System is in a safe state.\nSafe sequence is: ");
    for (i = 0; i < n; i++)
        printf("P%d ", safe_seq[i]);
    printf("\n");
    return 0;
}
// Enter the number of processes: 5
// Enter the number of resource types: 3
// Enter Allocation Matrix:
// 0 1 0
// 2 0 0
// 3 0 2
// 2 1 1
// 0 0 2
// Enter Max Matrix:
// 7 5 3
// 3 2 2
// 9 0 2
// 2 2 2
// 4 3 3
// Enter Available Resources:
// 3 3 2
// System is in a safe state.
// Safe sequence is: P1 P3 P4 P0 P2 
